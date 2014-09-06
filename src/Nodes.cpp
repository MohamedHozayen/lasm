#include "Nodes.h"
#ifndef _MSC_VER
#include <stdint.h>
#else
#include <cstdint>
#endif

BaseExpressionNode* BaseExpressionNode::getNextExpr(){
	return m_nextptr;

}

void BaseExpressionNode::setNextExpr(BaseExpressionNode* ptr){
	m_nextptr = ptr;
}


void BaseExpressionNode::setLineNumber(int lineno){
	m_line  = lineno;

}

int BaseExpressionNode::getLineNumber(){
	return m_line;

}

//================================================================


OpNode::OpNode(unsigned int nOpcodeID, Operands* op)
{

	m_id = nOpcodeID;
	m_aw = AW_UNSPECIFIED;
	ops = *op;
}

ExpressionType OpNode::getType(){
	return EXPR_OP;
}


const char* OpNode::getContent(){

	return SymTable::translateIDToName(m_id);;
}

Operands& OpNode::getOperands(){
	return ops;
}

void OpNode::setID(int id){
	m_id = id;
}
int OpNode::getOperandCount(){
	int tmp_len =0;
	for (unsigned int i = 0; i < ops.size();i++)
		tmp_len = tmp_len + !ops[i] ? 0 : 1;
	return tmp_len;
}

void OpNode::repr(int indentlevel){
	std::string indenter(indentlevel, '\t');	
	clog << indenter << "<statement>" << endl;
	clog << indenter << "\t<type>opcode</type>" << endl;
	clog << indenter << "\t<opcode>" << getContent() << "</opcode>" << endl;
		clog << indenter << "\t<id>" << m_id << "</id>" << endl;

	clog << indenter << "\t<params>" << endl;
	for (unsigned int i = 0; i < ops.size();i++)
	{
		if (ops[i])
			ops[i]->repr(indentlevel + 2);
	}
	clog << indenter << "\t</params>" << endl;
	clog << indenter << "</statement>" << endl;
	

}


AccessWidth OpNode::getExplicitAccessModifier(){
	return m_aw;
}
void OpNode::setExplicitAccessModifier(AccessWidth aw){
	m_aw = aw;
}



/*===========================================================*/
ControlNode::ControlNode(char* e, Operand* i){
	label = std::string(e+1);
 	ctrltype = ControlNode::decodeText(label);
	imm = i;
	m_key = std::string();
}

ControlNode::CtrlTypeLookupMap ControlNode::tlm(ControlNode::_populate());

ControlNode::CtrlTypeLookupMap  ControlNode::_populate(){

	ControlNode::CtrlTypeLookupMap ret;
	ret["db"] = CONTROL_DB;
	ret["dw"] = CONTROL_DW;
	ret["equ"] = CONTROL_EQU;
	ret["org"] = CONTROL_ORG;
	ret["end"] = CONTROL_END;
	return ret;

}

ExpressionType ControlNode::getType(){
	return EXPR_CONTROL;
}

ControlNodeType ControlNode::getControlType(){
	return ctrltype;
}

ControlNodeType ControlNode::decodeText(std::string& text){
	strToLowerCase(text);
	return tlm[text];
}

void ControlNode::repr(int indentlevel){
	std::string indenter(indentlevel, '\t');	
	clog << indenter << "<control>" << endl;
	clog << indenter << "\t<name>" << label << "</name>" << endl;
	clog << indenter << "\t<key>" << m_key << "<key>" << endl;
	clog << indenter << "\t<value>" << endl;
	imm->repr(indentlevel + 1);
		clog << indenter << "\t<value>" << endl;
	clog << indenter << "<control>" << endl;
}

void ControlNode::setContent(std::string a){
	label = a;
}

std::string& ControlNode::getContent(){
	return label;
}


void ControlNode::setImmediate(Immediate* im){
imm = im;

}

void ControlNode::setKey(char* a){
	m_key = std::string(a);

}

std::string& ControlNode::getKey(){
	return m_key;
}

Operand* ControlNode::getValue(){
	return imm;
}

LabelNode::LabelNode(char* a){
	m_label = std::string(a);
}

std::string& LabelNode::getContent(){
	return m_label;
}

void LabelNode::setContent(std::string a){
	m_label = a;
}

void LabelNode::repr(int indentlevel){
	std::string indenter(indentlevel, '\t');	
	clog << indenter << "<label>" << endl;
	clog << indenter << "\t<name>" << m_label << "</name>" << endl;
	clog << indenter << "<label>" << endl;
}

ExpressionType LabelNode::getType(){
	return EXPR_LABEL;
}

