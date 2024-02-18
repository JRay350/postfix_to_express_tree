/**
 * Title:   Lab 4 - tree_node.cpp
 * Purpose: To implement the operations of the TreeNode class, used as nodes for an expression tree.
 * Author: Jacob Ray
 * Date: May 18, 2023
 */

#include "tree_node.h"

/**
* Constructs a TreeNode with the given data and empty children pointers
* @param data the data to create a node of
*/
TreeNode::TreeNode(string data): _data(data), _right(nullptr), _left(nullptr) {
}

/**
* Setter for the right child of the caller node
* @param node the node to set the right child of
*/
void TreeNode::SetRight(TreeNode* node) {
    _right = node;
}

/**
* Setter for the left child of the caller node
* @param node the node to set the left child of
*/
void TreeNode::SetLeft(TreeNode* node) {
    _left = node;
}

/**
* Setter for the value data member of the caller
* @param value the value to set as the value of the node
*/
void TreeNode::SetValue(double value) {
    _value = value;
}

/**
* Setter for the operator data member of the caller
* @param op the operator character to set as the operator of the node
*/
void TreeNode::SetOperator(char op) {
    _operator = op;
}

/**
* Setter for the operand boolean data member of the caller, flagging whether the caller node is a operand or not
* @param value the bool value to set for the node
*/
void TreeNode::SetIsOperand(bool value) {
   _operand = value;
}

/**
* Setter for the id data member of the caller
* @param id the id value to set for the node
*/
void TreeNode::SetID(int id) {
    _id = id;
}

/**
* Setter for the parent data member of the caller
* @param parent the parent id value to set for the node
*/
void TreeNode::SetParent(int id) {
    _parent = id;
}

/**
* Getter for the data of the caller
* @return the number or operator represented by the node
*/
string TreeNode::GetData()const {
    return _data;
}

/**
* Getter for the right child of the caller
* @return a pointer to the right child
*/
TreeNode* TreeNode::GetRight()const {
    return _right;
}

/**
* Getter for the left child of the caller
* @return a pointer to the left child
*/
TreeNode* TreeNode::GetLeft()const {
    return _left;
}

/**
* Getter for the value data member of the caller
* @return the number represented by the node or the evaluation of its children if an operator node
*/
double TreeNode::GetValue()const {
    return _value;
}

/**
* Getter for the operator data member of the caller
* @return the operator symbol or a # character if an operand node
*/
char TreeNode::GetOperator()const {
    return _operator;
}

/**
* Getter for the flag of if the caller is an operand
* @return true if it is an operand, false if not
*/
bool TreeNode::IsOperand()const {
    return  _operand;
}

/**
* Getter for the id of the caller
* @return the id in the tree, starting at 0
*/
int TreeNode::GetID()const {
    return _id;
}

/**
* Getter for the id of the parent node of the caller
* @return the id of the caller's parent, or if it is the root, -1
*/
int TreeNode::GetParent()const {
    return _parent;
}