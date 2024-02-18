/**
 * Title:   Lab 4 - tree_node.h
 * Purpose: Declaration of the TreeNode class.
 * Author: Jacob Ray
 * Date: May 18, 2023
 */

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>

using std::string;

class TreeNode {
private:
    string _data;
    TreeNode* _right;
    TreeNode* _left;
    double _value;
    char _operator;
    bool _operand;
    int _id;
    int _parent;
public:
    TreeNode(string data);
    void SetRight(TreeNode* node);
    void SetLeft(TreeNode* node);
    void SetValue(double value);
    void SetOperator(char op);
    void SetIsOperand(bool value);
    void SetID(int id);
    void SetParent(int id);
    string GetData()const;
    TreeNode* GetRight()const;
    TreeNode* GetLeft()const;
    double GetValue()const;
    char GetOperator()const;
    bool IsOperand()const;
    int GetID()const;
    int GetParent()const;
};


#endif //POSTFIX_TO_EXPRESSION_TREE_ASSIGNMENT_TREE_NODE_H
