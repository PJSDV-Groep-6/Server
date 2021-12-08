#include "LinkedList.cpp"

int main() {
	LinkedList<int> dataList;
	Node<int> *node;
	int action, data;
	int id;
	size_t i;
	while (true) {
		std::cout << "Enter 0 to close, 1 to add an item, 2 to remove an item, 3 to show the content of a node." << std::endl;
		std::cin >> action;
		switch (action) {
			case 0:
				return 0;
			case 1:
				std::cout << "Enter an id for the message (duplicate ID's allowed): ";
				std::cin >> id;
				std::cout << "Enter an integer lower than 60000 for the data: ";
				std::cin >> data;
				dataList.addNode(id, data);
				break;
			case 2:
				std::cout << "Enter the id of the message to remove: ";
				std::cin >> id;
				dataList.deleteNode(id);
				break;
			case 3:
				std::cout << "Enter the id of the node from which to show the data: ";
				std::cin >> id;
				node = dataList.getNode(id);
				if (node != NULL) {
					std::cout << "[ " << node->getId() << ", " << node->getData() << ", " << node->getNext() << " ]" << std::endl;
				}
				else {
					std::cout << "Node not found!" << std::endl;
				}
				break;
			default:
					std::cout << "Invalid input." << std::endl;
		}
	}
}
