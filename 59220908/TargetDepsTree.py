
import pydot
import sys

graph = pydot.graph_from_dot_file(sys.argv[1])
result = {}

for g in graph:
	# print(g)
	for node in g.get_node_list():
		if node.get("label") != None:
			result[node.get("label")] = []

	for edge in g.get_edges():
		result[g.get_node(edge.get_source())[0].get("label")].append(g.get_node(edge.get_destination())[0].get("label"))

for r in result:
	print(r+":"+",".join(result[r]))