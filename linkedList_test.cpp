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
		if (action == 0) {
			break;
		}
		else if (action == 1) {
			std::cout << "Enter an id for the message (duplicate ID's allowed): ";
			std::cin >> id;
			std::cout << "Enter an integer lower than 60000 for the data: ";
			std::cin >> data;
			dataList.addNode(id, data);
		}
		else if (action == 2) {
			std::cout << "Enter the id of the message to remove: ";
			std::cin >> id;
			dataList.deleteNode(id);
		}
		else if (action == 3) {
			std::cout << "Enter the id of the node from which to show the data: ";
			std::cin >> id;
			node = dataList.getNode(id);
			if (node != NULL) {
				std::cout << "[ " << node->getId() << ", " << node->getData() << ", " << node->getNext() << " ]" << std::endl;
			}
			else {
				std::cout << "Node not found!" << std::endl;
			}
		}
		else {
			std::cout << "Invalid input." << std::endl;
		}
	}
}
