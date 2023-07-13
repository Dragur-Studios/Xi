#include "../Visual Elements/visual_element.h"

template<typename T>
VisualElement* XDocument::Q(const std::string& name)
{
	return Query<T>(_root, name);
}


template<typename T>
VisualElement* XDocument::Query(VisualElement* node, const std::string& name) {

    if (node == nullptr)
        return nullptr;

	if (node->_name == name && dynamic_cast<T*>(node) != nullptr) {
		return node;
	}


    for (auto& child : node->_children)
    {
        VisualElement* result = Query<T>(child, name);
        if (result != nullptr)
        {
            return result;
        }
    }

    return nullptr;

}