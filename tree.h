/**
 * Title:   Lab 4 - tree.h
 * Purpose: Declaration of the Tree class.
 * Author: Jacob Ray
 * Date: May 18, 2023
 */

#ifndef TREE_H
#define TREE_H

#include <stack>
#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::ostream;
using std::stringstream;
using std::stack;

#include "tree_node.h"


enum TraversalType {INORDER, PREORDER, POSTORDER};


class Tree {
private:
    TreeNode* _root;
    Tree(const Tree& other);
    const Tree& operator=(const Tree& rhs);
    void DeallocateTree(TreeNode* node);
    void SetNodeMembers(TreeNode* node, int& id, int parent);
    void PreOrderTraversalOutput(TreeNode* node, stringstream& output)const;
    void PostOrderTraversalOutput(TreeNode* node, stringstream& output)const;
    void InOrderTraversalOutput(TreeNode* node, stringstream& output)const;
    double TraversalEvaluate(TreeNode* node)const;
    void StepByStepEvaluation(TreeNode* node, ostream& output)const;
public:
    Tree();
    ~Tree();
    bool BuildTree(const string& postfixExpression);
    string Traverse(TraversalType traversalType)const;
    double Evaluate()const;
    void StepByStepEvaluation(ostream& output, bool useLevel = false)const;
};

#endif //POSTFIX_TO_EXPRESSION_TREE_ASSIGNMENT_TREE_H
