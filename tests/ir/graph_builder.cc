#include "ppl/nn/ir/full_graph_topo.h"
#include "ppl/nn/common/logger.h"
#include "tests/ir/graph_builder.h"
using namespace std;
using namespace ppl::common;

namespace ppl { namespace nn { namespace test {

GraphBuilder::GraphBuilder() {
    graph_.topo = make_shared<ir::FullGraphTopo>();
    graph_.data = make_shared<ir::GraphData>();
}

RetCode GraphBuilder::AddNode(const string& name, const ir::Node::Type& type, const vector<string>& inputs,
                              const vector<string>& outputs) {
    auto topo = graph_.topo.get();
    auto ret_pair = topo->AddNode(name);
    if (!ret_pair.second) {
        LOG(ERROR) << "node[" << name << "] already exists.";
        return RC_EXISTS;
    }
    auto node = ret_pair.first;

    node->SetType(type);

    for (auto x = inputs.begin(); x != inputs.end(); ++x) {
        auto edge_ret_pair = topo->AddEdge(*x);
        auto edge = edge_ret_pair.first;
        node->AddInput(edge->GetId());
        edge->AddConsumer(node->GetId());
    }

    for (auto x = outputs.begin(); x != outputs.end(); ++x) {
        auto edge_ret_pair = topo->AddEdge(*x);
        auto edge = edge_ret_pair.first;
        if (edge->GetProducer() != INVALID_NODEID) {
            LOG(ERROR) << "output[" << *x << "] already exists.";
            return RC_EXISTS;
        }
        node->AddOutput(edge->GetId());
        edge->SetProducer(node->GetId());
    }

    return RC_SUCCESS;
}

RetCode GraphBuilder::Finalize() {
    auto topo = graph_.topo.get();

    for (auto it = topo->CreateEdgeIter(); it->IsValid(); it->Forward()) {
        auto edge = it->Get();
        if (!edge->GetProducer()) {
            topo->MarkAsInput(edge->GetId());
        }
        if (edge->CalcConsumerCount() == 0) {
            topo->MarkAsOutput(edge->GetId());
        }
    }

    return RC_SUCCESS;
}

}}} // namespace ppl::nn::test
