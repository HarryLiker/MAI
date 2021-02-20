#pragma once

#include <list>
#include <stack>

#include "factory.hpp"

template<class T>
class Document {
private:
	struct Action;

	using figure_pointer = std::shared_ptr<Figure>;
	using action_pointer = std::shared_ptr<Action>;
	using const_iterator = std::list<figure_pointer>::const_iterator;

	std::list<figure_pointer> FiguresList;
	std::stack<action_pointer> ActionStack;

	struct Action {
		virtual void ActionPerform(Document &fact) = 0;
		virtual ~Action() {}
	};

	class DeleteAction: public Action {
	private:
		size_t DeletePosition;
	public:
		DeleteAction(const size_t &position) : DeletePosition(position) {}
		void ActionPerform(Document &document) override {
			document.Delete(DeletePosition);
		}
	};

	class AddAction: public Action {
	private:
		size_t AddPosition;
		figure_pointer AddFigure;
	public:
		AddAction(const size_t &position, const figure_pointer &figure) : AddPosition(position), AddFigure(figure) {}
		void ActionPerform(Document &document) override {
			document.AddFigure(AddPosition, AddFigure);
		}
	};
public:
	void CreateNew() {
		while (!ActionStack.empty()) {
			ActionStack.pop();
		}
		FiguresList.clear();
	}

	void SaveInFile(FILE *file) {
		size_t size = FiguresList.size(); // Number of figures in list
		fwrite(&size, sizeof(size_t), 1, file);
		for (const_iterator iterator = FiguresList.begin(); iterator != FiguresList.end(); ++iterator) {
			(*iterator)->Write(file);
		}
	}

	void LoadFromFile(FILE *file) {
		CreateNew();
		size_t size; // Number of figures in file
		fread(&size, sizeof(size_t), 1, file);
		for (size_t i = 0; i < size; ++i) {
			unsigned int type;
			fread(&type, sizeof(unsigned int), 1, file);
			if (type == RECTANGLE_ID_TYPE) {
				FiguresList.push_back(Factory<T, Rectangle<T>>::Read(file));
			} else if (type == TRAPEZE_ID_TYPE) {
				FiguresList.push_back(Factory<T, Trapeze<T>>::Read(file));
			} else if (type == RHOMBUS_ID_TYPE) {
				FiguresList.push_back(Factory<T, Rhombus<T>>::Read(file));
			}
		}
	}

	void Add(const size_t &position, const unsigned int &figure_id) {
		if (figure_id == RECTANGLE_ID_TYPE) {
			AddFigure(position, Factory<T, Rectangle<T>>::CreateFigure());
		} else if (figure_id == TRAPEZE_ID_TYPE) {
			AddFigure(position, Factory<T, Trapeze<T>>::CreateFigure());
		} else if (figure_id == RHOMBUS_ID_TYPE) {
			AddFigure(position, Factory<T, Rhombus<T>>::CreateFigure());
		}
	}

	void AddFigure(const size_t &position, const figure_pointer &figure) {
		if (position > FiguresList.size()) {
			FiguresList.push_back(figure);
			DeleteAction* delete_action = new DeleteAction(FiguresList.size());
			ActionStack.push(action_pointer(delete_action));
		} else {
			size_t current_position = 1;
			const_iterator iterator = FiguresList.begin();
			while (current_position < position) {
				++current_position;
				++iterator;
			}
			FiguresList.insert(iterator, figure);
			DeleteAction* delete_action = new DeleteAction(position);
			ActionStack.push(action_pointer(delete_action));
		}
	}

	void Delete(const size_t &position) {
		if (FiguresList.empty()) {
			std::cout << "Nothing to delete!" << std::endl;
			return;
		}
		if (position > FiguresList.size()) {
			AddAction* addAct = new AddAction(FiguresList.size() - 1, FiguresList.back());
			ActionStack.push(action_pointer(addAct));
			FiguresList.pop_back();
		} else {
			size_t current_position = 1;
			const_iterator iterator = FiguresList.begin();
			while (current_position < position) {
				++current_position;
				++iterator;
			}
			AddAction* addAct = new AddAction(current_position, *iterator);
			ActionStack.push(action_pointer(addAct));
			FiguresList.erase(iterator);
		}
	}

	void Undo() {
		if (ActionStack.empty()) {
			std::cout << "Nothing to undo!" << std::endl;
		} else {
			ActionStack.top()->ActionPerform(*this);
			ActionStack.pop();
			ActionStack.pop();
			std::cout << "The last action was canseled\n";
		}
	}

	template<class U>
	friend std::ostream &operator<< (std::ostream &out, const Document<U> &document) {
		Document::const_iterator iterator = document.FiguresList.begin();
		for (size_t i = 0; i < document.FiguresList.size(); ++i) {
			out << i + 1 << ". ";
			(*iterator)->Print(out);
			out << "\n";
			++iterator;
		}
		return out;
	}
};