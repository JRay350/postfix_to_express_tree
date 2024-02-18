/**
 * Title:   Lab 4 - tree.cpp
 * Purpose: To implement the operations of the Tree class, used to implement an expression tree.
 * Author: Jacob Ray
 * Date: May 18, 2023
 */

#include "tree.h"
#include <cctype>
#include <cmath>
#include <iomanip>

using std::stack;
using std::stod;
using std::fixed;
using std::setprecision;

/**
* Constructs an empty tree
*/
Tree::Tree(): _root(nullptr) {
}

/**
* Unimplemented copy constructor of a tree
* @param other the other tree to copy from
*/
Tree::Tree(const Tree& other) {
}

/**
* Unimplemented copy assignment operator of a tree
* @param rhs the other tree to copy from
* @return the caller
*/
const Tree& Tree::operator=(const Tree& rhs) {
    return *this;
}

/**
* Destructor to deallocate all nodes of the tree
*/
Tree::~Tree() {
    if (_root != nullptr) {
        DeallocateTree(_root);
    }
}

/**
* Helper function used in destructor to recursively deallocate each node in the tree via postorder traversal
* @param node current node being operated on
*/
void Tree::DeallocateTree(TreeNode* node) {
    if (node == nullptr) { // Base case for empty node
        return;
    }
    DeallocateTree(node->GetLeft()); // Delete left tree
    DeallocateTree(node->GetRight()); // Delete right tree
    delete node; // Delete current node
}

/**
* Helper function to traverse in preorder and write to output each node's data
* @param node current node being operated on
* @param output the stream to write to
*/
void Tree::PreOrderTraversalOutput(TreeNode* node, stringstream& output)const {
    if (node == nullptr) { // Base case for empty node
        return;
    }
    output << node->GetData() << " "; // Output current node
    PreOrderTraversalOutput(node->GetLeft(), output); // Output left tree
    PreOrderTraversalOutput(node->GetRight(), output); // Output right tree
}

/**
* Helper function to traverse in postorder and write to output each node's data
* @param node current node being operated on
* @param output the stream to write to
*/
void Tree::PostOrderTraversalOutput(TreeNode* node, stringstream& output)const {
    if (node == nullptr) { // Base case for empty node
        return;
    }
    PostOrderTraversalOutput(node->GetLeft(), output); // Output left tree
    PostOrderTraversalOutput(node->GetRight(), output); // Output right tree
    output << node->GetData() << " "; // Output current node
}

/**
* Helper function to traverse inorder and write to output each node's data
* @param node current node being operated on
* @param output the stream to write to
*/
void Tree::InOrderTraversalOutput(TreeNode* node, stringstream& output)const {
    if (node == nullptr) { // Base case for empty node
        return;
    }
    InOrderTraversalOutput(node->GetLeft(), output); // Output left tree
    output << node->GetData() << " "; // Output current node
    InOrderTraversalOutput(node->GetRight(), output); // Output right tree
}

/**
* Helper function to evaluate a tree recursively by traversing postfix and evaluating leaves (numbers) using operators (internal nodes)
* @param node current node being operated on
* @return the data of the node if a leaf or the evaluation of the children if an internal node or the root is caller
*/
double Tree::TraversalEvaluate(TreeNode* node)const {
    if (node->GetLeft() == nullptr && node->GetRight() == nullptr) { // Base case for numbers (the leaves of the tree)
        return stod(node->GetData()); // Return data of node as double
    }

    // Beyond this is code only reached for operator nodes (internal nodes)
    double leftChild = TraversalEvaluate(node->GetLeft()); // Evaluate left tree
    double rightChild = TraversalEvaluate(node->GetRight()); // Evaluate right tree

    if (node->GetData() == "*") { // Multiplication internal node
        return leftChild * rightChild;
    } else if (node->GetData() == "/") { // Division internal node
        return leftChild / rightChild;
    } else if (node->GetData() == "+") { // Addition internal node
        return leftChild + rightChild;
    } else if (node->GetData() == "-") { // Subtraction internal node
        return leftChild - rightChild;
    }
    // Power internal node
    return pow(leftChild, rightChild);
}

/**
* Helper function to set the node members later used in step by step evaluation output
* @param node current node being operated on
* @param id counter for incrementing id as each node is visited
* @param parent tracks id of parent for the children to hold
*/
void Tree::SetNodeMembers(TreeNode* node, int& id, int parent) {
    if (node == nullptr) { // Base case for empty node
        return;
    }

    // Set id member, increment id, and set parent id
    node->SetID(id);
    id++;
    node->SetParent(parent);

    // Set if node is operand, the operator char, and the value of the number or evaluation of the operator's children
    if (isdigit(node->GetData().at(0))) { // If node is an operand
        node->SetIsOperand(true);
        node->SetOperator('#');
        node->SetValue(stod(node->GetData()));
    } else { // If node is operator
        node->SetIsOperand(false);
        node->SetOperator(node->GetData().at(0));
        node->SetValue(TraversalEvaluate(node));
    }

    SetNodeMembers(node->GetLeft(), id, node->GetID()); // Set members of the left child tree
    SetNodeMembers(node->GetRight(), id, node->GetID()); // Set members of the right child tree
}

/**
* Helper function to output the step by step evaluation
* @param node current node being operated on
* @param output the stream to send the output to
*/
void Tree::StepByStepEvaluation(TreeNode* node , ostream& output)const {
    if (node == nullptr) { // Base case for empty node
        return;
    }

    output << fixed << setprecision(2) << "{\"value\":" << node->GetValue() << ", \"operator\":\"" << node->GetOperator() << "\", \"operand\":";
    if (node->IsOperand()) { // If node is an operand
        output << "true";
    } else { // If node is operator
        output << "false";
    }
    output << ", \"id\":" << node->GetID() << ", \"parent\":" << node->GetParent() << "}\n";

    StepByStepEvaluation(node->GetLeft(), output); // Output the left child tree
    StepByStepEvaluation(node->GetRight(), output); // Output the right child tree
}

/**
* Builds an expression tree given a postfix expression and sets the data members of the nodes
* @param postfixExpression the expression to build the tree off of
* @return true if the build was successful, false if not
*/
bool Tree::BuildTree(const string& postfixExpression) {
    stringstream input;
    input.str(postfixExpression);
    string token;

    // Used to form tree by stacking all numbers and symbols
    stack<TreeNode*> treeNodes;

    // While there is a token in the postfix expression string to process still
    while (input >> token) {
        if (isdigit(token.at(0))) { // If token is a number
            treeNodes.push(new TreeNode(token));
        } else { // If token is an operator symbol
            TreeNode* curr = new TreeNode(token);
            // Pair each operator with a numerical left and right child (or expression result)
            curr->SetRight(treeNodes.top());
            treeNodes.pop();
            curr->SetLeft(treeNodes.top());
            treeNodes.pop();
            treeNodes.push(curr); // Push the mini tree back into the stack to later be used as a child or as root
        }
    }
    _root = treeNodes.top();
    treeNodes.pop();
    if (!treeNodes.empty()) { // The root should be the last node in the stack, otherwise building has failed
        return false;
    }

    int count = 0; // Counter for index of processed tree nodes
    SetNodeMembers(_root, count, -1); // -1 passed in as parent of the root

    return true;
}

/**
* Traverse and output the nodes of the tree in either post, pre, or inorder depending on the argument passed
* @param traversalType type of traversal to output the nodes in
* @return the output of all the nodes traversed
*/
string Tree::Traverse(TraversalType traversalType)const {
    stringstream output;
    if (traversalType == PREORDER) {
        PreOrderTraversalOutput(_root, output);
    } else if (traversalType == POSTORDER) {
        PostOrderTraversalOutput(_root, output);
    } else {
        InOrderTraversalOutput(_root, output);
    }
    string retVal = output.str();
    return retVal.substr(0, retVal.size() - 1); // Trim off the trailing space
}

/**
* Evaluate the entire expression tree
* @return the evaluation result
*/
double Tree::Evaluate()const {
    return TraversalEvaluate(_root);
}

/**
* Output the evaluation step by step of the tree in preorder, with each node in JSON form being output
* @param output the stream to output to
* @param useLevel to determine whether to visually illustrate hierarchy
*/
void Tree::StepByStepEvaluation(ostream& output, bool useLevel)const {
    StepByStepEvaluation(_root, output);
}