#ifndef IncludedMathMatrixStackH
#define IncludedMathMatrixStackH

//===========================================================================
// Filename:	Matrix.h
// Author:		Jarrod MacKay
// Description:	Stack that keeps the current matrix multiplication order
//				and result.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "../Abstracts/Stack.h"
#include "Algebra.h"

//===========================================================================
// Classes
//===========================================================================

namespace Mathematics
{
	class MatrixStack
	{
	//Attributes
	private:

		struct MatrixPush
		{
			Matrix44 Pushed;
			Matrix44 Result;
		};

		Abstracts::Stack<MatrixPush> m_Matrices;

	//Operators
	public:

		MatrixStack();

		~MatrixStack();

		NonCopyable(MatrixStack);

	//Methods
	public:

		void Push();

		void Push(const Matrix44& p_Matrix);

		void Pop();

		void Reset();

		const Matrix44 GetResult() const;
	};

} // namespace Mathematics

#endif //#ifndef IncludedMathMatrixStackH