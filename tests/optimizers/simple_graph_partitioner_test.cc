#include "ppl/nn/optimizers/simple_graph_partitioner.h"
#include "ppl/nn/runtime/runtime_graph_info.h"

#include "gtest/gtest.h"
#include "tests/ir/graph_builder.h"
#include "tests/engines/tmp_engine.h"

#include <vector>
#include <memory>

using namespace std;
using namespace ppl::nn;
using namespace ppl::common;
using namespace ppl::nn::test;

class TestGraphPartion : public testing::Test {
protected:
    virtual void SetUp() override {
        builder_.SetGraphName("tmp");
        builder_.AddNode("a", ir::Node::Type("test", "op1"), {"input_of_a"}, {"output_of_a"});
        builder_.AddNode("b", ir::Node::Type("test", "op2"), {"output_of_a"}, {"output_of_b"});
        builder_.AddNode("c", ir::Node::Type("test", "op3"), {"output_of_b"}, {"output_of_c"});
        builder_.AddNode("d", ir::Node::Type("test", "op4"), {"output_of_c"}, {"output_of_d"});
        builder_.Finalize();
    }

    GraphBuilder builder_;
};

TEST_F(TestGraphPartion, partition1) {
    auto resource = make_shared<utils::SharedResource>();
    auto graph_info = make_shared<RuntimeGraphInfo>();
    resource->engines.reserve(2);
    resource->engines.emplace_back(unique_ptr<EngineImpl>(new TmpEngineOne()));
    resource->engines.emplace_back(unique_ptr<EngineImpl>(new TmpEngineTwo()));
    SimpleGraphPartitioner partitioner;
    vector<pair<EngineImpl*, vector<nodeid_t>>> partitions;
    auto status = partitioner.Partition(resource.get(), builder_.GetGraph(), &partitions);
    EXPECT_EQ(status, RC_SUCCESS);
    EXPECT_EQ(partitions.size(), 2);
    for (auto partition : partitions) {
        if (string(partition.first->GetName()) == "tmpOne") {
            for (auto node_id : partition.second) {
                EXPECT_TRUE(node_id == 0 || node_id == 1);
            }
        }
        if (string(partition.first->GetName()) == "tmpTwo") {
            for (auto node_id : partition.second) {
                EXPECT_TRUE(node_id == 2 || node_id == 3);
            }
        }
    }
}
