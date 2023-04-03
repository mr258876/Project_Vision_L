#ifndef _BUTTON_TICKER_H_
#define _BUTTON_TICKER_H_

#include <LinkedList.h>
#include <OneButton.h>

struct ButtonTicker_Button_t
{
    OneButton *btn;
    const char *name;
};

class ButtonTicker
{
private:
    LinkedList<ButtonTicker_Button_t> _buttons;

    ListNode<ButtonTicker_Button_t> *getNode(int id);
    ListNode<ButtonTicker_Button_t> *getNode(const char *name);

public:
    ButtonTicker(/* args */);
    ~ButtonTicker();

    void tick();
    int assign(ButtonTicker_Button_t btn);
    ButtonTicker_Button_t *get(int id);
    ButtonTicker_Button_t *get(const char *name);
};

ButtonTicker::ButtonTicker(/* args */)
{
}

ButtonTicker::~ButtonTicker()
{
}

void ButtonTicker::tick()
{
    ListNode<ButtonTicker_Button_t> *node = _buttons.getRoot();
    while (node)
    {
        node->data.btn->tick();
        node = node->next;
    }
}

int ButtonTicker::assign(ButtonTicker_Button_t btn)
{
    _buttons.add(btn);
    return _buttons.size() - 1;
}

ListNode<ButtonTicker_Button_t> *ButtonTicker::getNode(int id)
{
    if (id < _buttons.size())
    {
        return _buttons.getNode(id);
    }
    return NULL;
}

ListNode<ButtonTicker_Button_t> *ButtonTicker::getNode(const char *name)
{
    ListNode<ButtonTicker_Button_t> *node = _buttons.getRoot();
    while (node)
    {
        if (strcasecmp(name, node->data.name))
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

ButtonTicker_Button_t *ButtonTicker::get(int id)
{
    ListNode<ButtonTicker_Button_t> *node = getNode(id);
    if (node)
        return &node->data;
    return NULL;
}

ButtonTicker_Button_t *ButtonTicker::get(const char *name)
{
    ListNode<ButtonTicker_Button_t> *node = getNode(name);
    if (node)
        return &node->data;
    return NULL;
}

#endif