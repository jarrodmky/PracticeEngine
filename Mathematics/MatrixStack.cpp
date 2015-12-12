#include "Precompiled.h"
#include "MatrixStack.h"

using namespace Mathematics;

//===========================================================================
// Function Definitions
//===========================================================================

MatrixStack::MatrixStack()
	: m_Matrices()
{
	Reset();
}

MatrixStack::~MatrixStack()
{
	m_Matrices.Destroy();
}

void MatrixStack::Push()
{
	MatrixPush thisPush;
	m_Matrices.Peek(thisPush);
	m_Matrices.Push(thisPush);
}

void MatrixStack::Push(const Matrix44& p_Matrix)
{
	MatrixPush thisPush;
	MatrixPush lastPush;
	m_Matrices.Peek(lastPush);
	thisPush.Pushed = p_Matrix;
	thisPush.Result = lastPush.Result * p_Matrix;
	m_Matrices.Push(thisPush);
}

void MatrixStack::Pop()
{
	MatrixPush thisPop;
	m_Matrices.Pop(thisPop);
}

void MatrixStack::Reset()
{
	m_Matrices.Clear();

	MatrixPush firstPush;
	firstPush.Pushed = I4();
	firstPush.Result = I4();
	m_Matrices.Push(firstPush);
}

const Matrix44 MatrixStack::GetResult() const
{
	MatrixPush topPush;
	m_Matrices.Peek(topPush);
	return topPush.Result;
}