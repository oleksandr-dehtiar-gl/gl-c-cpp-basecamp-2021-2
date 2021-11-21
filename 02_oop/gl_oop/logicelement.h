#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H


class LogicElement
{
public:

    LogicElement(int input_amount);
    virtual ~LogicElement();
    virtual void updateLogic() = 0;
    virtual bool getOutput() const = 0;

protected:
    bool m_output;
    char m_inputs;
    int  m_input_amount;
};

#endif // LOGICELEMENT_H
