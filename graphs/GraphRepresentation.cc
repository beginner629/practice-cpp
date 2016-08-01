#include "GraphRepresentation.h"

namespace jw {

const std::string GraphRepresentation::kRepresentationTypeList{"list"};
const std::string GraphRepresentation::kRepresentationTypeMatrix{"matrix"};
const std::string GraphRepresentation::kGraphTypeDirected{"directed"};
const std::string GraphRepresentation::kGraphTypeUndirected{"undirected"};

std::unique_ptr<jw::GraphRepresentation> GraphRepresentation::GetRepresentation(
    const std::string representation_type, const std::string graph_type) {
  if (representation_type == kRepresentationTypeList) {
    return std::unique_ptr<GraphRepresentation>{
        new GraphRepresentationList(graph_type)};
  } else if (representation_type == kRepresentationTypeMatrix) {
    return std::unique_ptr<GraphRepresentation>{
        new GraphRepresentationMatrix(graph_type)};
  } else {
    std::cerr << "Graph Representation type not supported.";
    exit(EXIT_FAILURE);
  }
}

GraphRepresentation::GraphRepresentation(const std::string graph_type) {
  vertices_ = {0};

  if (graph_type == kGraphTypeDirected) {
    type_ = kGraphTypeDirected;
  } else if (graph_type == kGraphTypeDirected) {
    type_ = kGraphTypeUndirected;
  }
}

void GraphRepresentationList::AddEdge(const int source, const int destination) {
  unsigned long source_index = static_cast<unsigned long>(source);
  int size_required = std::max(source, destination) + 1;

  while (adj_list_.size() < size_required) {
    adj_list_.push_back(std::vector<int>());
  }

  auto adjacent_vertices = adj_list_.at(source_index);

  // find it so we don't add edge twice
  std::vector<int>::iterator it;
  it = std::find(adjacent_vertices.begin(), adjacent_vertices.end(),
                 destination);

  if (it == adjacent_vertices.end()) {
    adj_list_.at(source_index).push_back(destination);
  }
}

void GraphRepresentationList::PrintDebug() {
  std::cout << "Adjacency list:" << std::endl;
  std::cout << "Vertices: " << adj_list_.size() - 1 << std::endl;

  for (unsigned long i = 0; i < adj_list_.size(); ++i) {
    std::cout << "Vertex: " << i << ":";
    for (unsigned long j = 0; j < adj_list_[i].size(); ++j) {
      std::cout << " " << adj_list_.at(i).at(j);
    }
    std::cout << std::endl;
  }
}

void GraphRepresentationMatrix::AddEdge(const int source,
                                        const int destination) {
  std::cout << "down in matrix " << std::endl;
}

void GraphRepresentationMatrix::PrintDebug() {
  std::cout << "Adjacency matrix:" << std::endl;
  std::cout << "Vertices: " << vertices_ << std::endl;
}

}  // namespace jw