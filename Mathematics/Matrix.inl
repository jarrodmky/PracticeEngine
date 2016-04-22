//===========================================================================
// Filename:	Matrix.inl
// Author:		Jarrod MacKay
//===========================================================================

namespace Mathematics
{
	namespace
	{
		const scalar inverseErrorTolerance(0.00001f);

		//===========================================================================
		// Class Helpers
		//===========================================================================

		//from numerical recipes Press, Teukolsky et al.
		template <u32 t_Rank>
		class MatrixDecomposition
		{
			//Attributes
		private:

			Matrix<t_Rank, t_Rank> m_LU;
			IntVector<t_Rank> m_Permutation;
			scalar m_Determinant;
			const Matrix<t_Rank, t_Rank>& m_Matrix;
			bool m_Singular;

			//Operators
		public:

			MatrixDecomposition(const Matrix<t_Rank, t_Rank>& p_Matrix)
				: m_LU(p_Matrix)
				, m_Permutation()
				, m_Determinant(NotANumber)
				, m_Matrix(p_Matrix)
				, m_Singular(false)
			{
				RealVector<t_Rank> scaling; //stores the implicit scaling of each row.
				m_Determinant = Unity; //no row ops 

				//get the scaling information for each row
				for(u32 i = 0; i < t_Rank; ++i)
				{
					scalar big = 0.0;
					for(u32 j = 0; j < t_Rank; ++j)
					{
						scalar temp = AbsoluteValue(m_LU(i, j));
						if(temp > big)
						{
							big = temp;
						}
					}

					//check for singularity
					if(IsZero(big))
					{
						FlagSingularity();
						return;
					}
					scaling(i) = Unity / big;
				}

				//decompose
				for(u32 k = 0; k < t_Rank; ++k)
				{
					//find largest pivot element.
					u32 iMax = static_cast<u32>(-1);
					scalar big = 0.0;
					for(u32 i = k; i < t_Rank; ++i)
					{
						scalar temp = scaling(i) * AbsoluteValue(m_LU(i, k));
						if(temp > big)
						{
							big = temp;
							iMax = i;
						}
					}

					//check for singularity
					if(iMax == -1 || IsZero(big))
					{
						FlagSingularity();
						return;
					}

					//interchange rows if necessary
					if(k != iMax)
					{
						m_LU.SwitchRows(iMax, k);
						m_Determinant = -m_Determinant;
						scaling(iMax) = scaling(k);// Also interchange the scale factor.
					}
					m_Permutation(k) = iMax;

					//check for singularity
					if(IsZero(m_LU(k, k)))
					{
						m_LU(k, k) = Zero;
						FlagSingularity();
						return;
					}

					//reduce submatrix
					for(u32 i = k + 1; i < t_Rank; ++i)
					{
						scalar temp = m_LU(i, k) /= m_LU(k, k);
						for(u32 j = k + 1; j < t_Rank; ++j)
						{
							m_LU(i, j) -= temp * m_LU(k, j);
						}
					}
				}

				//calculate determinant
				RealVector<t_Rank> diag = m_LU.Diagonal();
				for(u32 i = 0; i < t_Rank; i++)
				{
					if(IsZero(diag(i)))
					{
						FlagSingularity();
						return;
					}
					m_Determinant *= diag(i);
				}
			}

		private:

			NonCopyable(MatrixDecomposition<t_Rank>);

			//Methods
		public:

			void Solve(const RealVector<t_Rank>& p_Constant, RealVector<t_Rank>& p_Solution)
			{
				for(u32 i = 0; i < t_Rank; ++i)
				{
					p_Solution(i) = p_Constant(i);
				}

				//for each row unscramble permutation
				u32 pivot = 0;
				for(u32 i = 0; i < t_Rank; ++i)
				{
					u32 iPermute = m_Permutation(i);
					scalar sum = p_Solution(iPermute);
					p_Solution(iPermute) = p_Solution(i);
					if(pivot != 0)
					{
						for(u32 j = pivot - 1; j < i; ++j)
						{
							sum -= m_LU(i, j) * p_Solution(j);
						}
					}
					else if(sum != 0.0) //encountered nonzero
					{
						pivot = i + 1;
					}
					p_Solution(i) = sum;
				}

				//back substitute
				for(s64 i = t_Rank - 1; i >= 0; --i)
				{
					u32 i32 = static_cast<u32>(i);
					scalar sum = p_Solution(i32);
					for(u32 j = i32 + 1; j < t_Rank; ++j)
					{
						sum -= m_LU(i32, j) * p_Solution(j);
					}
					p_Solution(i32) = sum / m_LU(i32, i32);
				}
			}

			template <u32 t_Sets>
			void Solve(const Matrix<t_Rank, t_Sets>& p_Constant, Matrix<t_Rank, t_Sets>& p_Solution)
			{
				RealVector<t_Rank> solutionCol;
				for(u32 j = 0; j < t_Sets; ++j)
				{
					for(u32 i = 0; i < t_Rank; ++i)
					{
						solutionCol(i) = p_Constant(i, j);
					}
					Solve(solutionCol, solutionCol);
					for(u32 i = 0; i < t_Rank; ++i)
					{
						p_Solution(i, j) = solutionCol(i);
					}
				}
			}

			void Inverse(Matrix<t_Rank, t_Rank>& p_Inverse)
			{
				for(u32 i = 0; i < t_Rank; ++i)
				{
					for(u32 j = 0; j < t_Rank; ++j)
					{
						p_Inverse(i, j) = Zero;
					}
					p_Inverse(i, i) = Unity;
				}
				Solve(p_Inverse, p_Inverse);
			}

			scalar Determinant()
			{
				return (IsSingular()) ? (Zero) : m_Determinant;
			}

			void Improve(const RealVector<t_Rank>& p_Constant, RealVector<t_Rank>& p_Solution)
			{
				RealVector<t_Rank> error;
				for(u32 i = 0; i < t_Rank; ++i)
				{
					f64 accum = -p_Constant(i);
					for(u32 j = 0; j < t_Rank; ++j)
					{
						accum += static_cast<64>(m_Matrix(i, j)) * static_cast<64>(p_Solution(j));
					}
					error(i) = accum;
				}

				//solve for and subtract error term
				Solve(error, error);
				for(u32 i = 0; i < t_Rank; ++i)
				{
					p_Solution(i) -= error(i);
				}
			}

			inline bool IsSingular()
			{
				return m_Singular;
			}

		private:

			inline void FlagSingularity()
			{
				m_Determinant = Zero;
				m_Singular = true;
			}
		};


		template <u32 t_Rank>
		struct SymmetricEigendecomposition
		{
		private:
			Matrix<t_Rank, t_Rank> z;
			RealVector<t_Rank> d;
			RealVector<t_Rank> e;
			bool symmetric;
			bool yesvecs;
		public:
			SymmetricEigendecomposition(const Matrix<t_Rank, t_Rank>& a, bool yesvec = true)
				: z(a)
				, d()
				, e()
				, symmetric(true)
				, yesvecs(yesvec)
			{
				tred2(); //reduce to tridiagonal form
				tqli(); //solve eigensystem of tridiagonal matrix
				sort();
			}

			void tred2()
			{
				s32 l, k, j, i;
				scalar scale, hh, h, g, f;
				for(i = t_Rank - 1; i > 0; --i)
				{
					l = i - 1;
					h = scale = Zero;
					if(l > 0)
					{
						for(k = 0; k < i; ++k)
						{
							scale += abs(z(i, k));
						}
						if(scale == 0.0)
						{
							e(i) = z(i, l);
						}
						else
						{
							for(k = 0; k < i; ++k)
							{
								z(i, k) /= scale;
								h += z(i, k) * z(i, k);
							}
							f = z(i, l);
							g = (f >= 0.0) ? (-sqrt(h)) : (sqrt(h));
							e(i) = scale*g;
							h -= f*g;
							z(i, l) = f - g;
							f = 0.0;
							for(j = 0; j < i; ++j)
							{
								if(yesvecs)
								{
									z(j, i) = z(i, j) / h;
								}
								g = 0.0;
								for(k = 0; k < j + 1; ++k)
								{
									g += z(j, k) * z(i, k);
								}
								for(k = j + 1; k < i; ++k)
								{
									g += z(k, j) * z(i, k);
								}
								e(j) = g / h;
								f += e(j) * z(i, j);
							}
							hh = f / (h + h);
							for(j = 0; j < i; ++j)
							{
								f = z(i, j);
								e(j) = g = e(j) - hh*f;
								for(k = 0; k < j + 1; ++k)
								{
									z(j, k) -= (f*e(k) + g*z(i, k));
								}
							}
						}
					}
					else
					{
						e(i) = z(i, l);
					}
					d(i) = h;
				}
				if(yesvecs)
				{
					d(0) = 0.0;
				}
				e(0) = 0.0;
				for(i = 0; i < t_Rank; ++i)
				{
					if(yesvecs)
					{
						if(d(i) != 0.0)
						{
							for(j = 0; j < i; ++j)
							{
								g = 0.0;
								for(k = 0; k < i; ++k)
								{
									g += z(i, k) * z(k, j);
								}
								for(k = 0; k < i; ++k)
								{
									z(k, j) -= g*z(k, i);
								}
							}
						}
						d(i) = z(i, i);
						z(i, i) = Unity;
						for(j = 0; j < i; ++j)
						{
							z(j, i) = z(i, j) = 0.0;
						}
					}

					else
					{
						d(i) = z(i, i);
					}
				}
			}


			void tqli()
			{
				s32 m, l, iter, i, k;
				scalar s, r, p, g, f, dd, c, b;
				for(i = 1; i < t_Rank; ++i)
				{
					e(i - 1) = e(i);
				}
				e(t_Rank - 1) = Zero;
				for(l = 0; l < t_Rank; ++l)
				{
					iter = 0;
					do
					{
						for(m = l; m < t_Rank - 1; ++m)
						{
							dd = abs(d(m)) + abs(d(m + 1));
							if(abs(e(m)) <= Epsilon*dd) break;
						}
						if(m != l)
						{
							if(iter++ == 30)
							{
								Halt("Too many iterations");
							}
							g = (d(l + 1) - d(l)) / (2.0f*e(l));
							r = pythag(g, 1.0);
							g = d(m) - d(l) + e(l) / (g + Signum(r, g));
							s = c = 1.0;
							p = 0.0;
							for(i = m - 1; i >= l; i--)
							{
								f = s*e(i);
								b = c*e(i);
								e(i + 1) = (r = pythag(f, g));
								if(r == 0.0)
								{
									d(i + 1) -= p;
									e(m) = 0.0;
									break;
								}
								s = f / r;
								c = g / r;
								g = d(i + 1) - p;
								r = (d(i) - g)*s + 2.0f*c*b;
								d(i + 1) = g + (p = s*r);
								g = c*r - b;
								if(yesvecs)
								{
									for(k = 0; k < t_Rank; k++)
									{
										f = z(k,i + 1);
										z(k,i + 1) = s*z(k,i) + c*f;
										z(k,i) = c*z(k,i) - s*f;
									}
								}
							}
							if(r == 0.0 && i >= l) continue;
							d(l) -= p;
							e(l) = g;
							e(m) = 0.0;
						}
					} while(m != l);
				}
			}

			scalar pythag(const scalar A, const scalar B)
			{
				scalar absA = AbsoluteValue(A);
				scalar absB = AbsoluteValue(B);
				scalar divBA = absB / absA;
				scalar divAB = absA / absB;
				return (absA > absB ? absA * std::sqrt(Unity + divBA * divBA) :
						(IsZero(absB) ? Zero : absB * std::sqrt(Unity + divAB * divAB)));
			}

			void sort()
			{
				if(yesvecs)
					eigsrt(d, &z);
				else
					eigsrt(d);
			}

			static void eigsrt(RealVector<t_Rank>& d, Matrix<t_Rank, t_Rank>* v = nullptr)
			{
				u32 k;
				for(u32 i = 0; i < t_Rank - 1; ++i)
				{
					scalar p = d(k = i);
					for(u32 j = i; j < t_Rank; ++j)
					{
						if(d(j) >= p)
						{
							p = d(k = j);
						}
					}
					if(k != i)
					{
						d(k) = d(i);
						d(i) = p;
						if(v != nullptr)
						{
							for(u32 j = 0; j < t_Rank; ++j)
							{
								p = (*v)(j, i);
								(*v)(j, i) = (*v)(j, k);
								(*v)(j, k) = p;
							}
						}
					}
				}
			}

			void Eigenvalues(RealVector<t_Rank>& p_Vector)
			{
				p_Vector = d;
			}

			void Eigenvectors(Matrix<t_Rank, t_Rank>& p_Matrix)
			{
				p_Matrix = z;
			}
		};
	}

	//===========================================================================
	// Operators Definitions
	//===========================================================================

	template <u32 t_Rows, u32 t_Columns>
	inline const Matrix<t_Rows, t_Columns> operator *(const scalar p_Lhs, const Matrix<t_Rows, t_Columns>& p_Rhs)
	{
		return p_Rhs * p_Lhs;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const RealVector<t_Rows> operator *(const Matrix<t_Rows, t_Columns>& p_Lhs, const RealVector<t_Columns>& p_Rhs)
	{
		RealVector<t_Rows> sum(0.0f);

		for(u32 i = 0; i < t_Columns; ++i)
		{
			sum += (p_Lhs.Column(i) * p_Rhs(i));
		}

		return sum;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& operator *=(Matrix<t_Rows, t_Columns>& p_Lhs, const Matrix<t_Columns, t_Columns>& p_Rhs)
	{
		p_Lhs = p_Lhs * p_Rhs;
		return p_Lhs;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rank>
	inline const Matrix<t_Rank, t_Rank> operator ^(const RealVector<t_Rank>& p_Lhs, const RealVector<t_Rank>& p_Rhs)
	{
		Matrix33 temp;

		for(u32 i = 0; i < t_Rank; ++i)
		{
			for(u32 j = 0; j < i; ++j)
			{
				temp(i, j) = temp(j, i) = p_Lhs(i) * p_Rhs(j);
			}
		}

		return temp;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rank>
	inline const Matrix<t_Rank, t_Rank> In()
	{
		Matrix<t_Rank, t_Rank> M(Zero);
		for(u32 i = 0; i < t_Rank; ++i)
		{
			M(i, i) = Unity;
		}
		return M;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Inner, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> operator *(const Matrix<t_Rows, t_Inner>& p_Lhs, const Matrix<t_Inner, t_Columns>& p_Rhs)
	{
		Matrix<t_Rows, t_Columns> M(Zero);
		for(u32 i = 0; i < t_Rows; ++i)
		{
			for(u32 j = 0; j < t_Columns; ++j)
			{
				M(i, j) = p_Lhs.TransposedRow(i) | p_Rhs.Column(j);
			}
		}

		return M;
	}

	//===========================================================================
	// Function Definitions
	//===========================================================================

	template <u32 t_Rows, u32 t_Columns>
	inline const bool Close(const Matrix<t_Rows, t_Columns>& p_Lhs
							, const Matrix<t_Rows, t_Columns>& p_Rhs
							, const scalar p_Tolerance)
	{
		return IsApproximatelyZero((p_Lhs - p_Rhs).NormSquared(), p_Tolerance);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	inline const bool ApproximatelyEqual(const Matrix<t_Rows, t_Columns>& p_Lhs
										 , const Matrix<t_Rows, t_Columns>& p_Rhs
										 , const scalar p_Tolerance)
	{
		for(u32 i = 0; i < t_Columns; ++i)
		{
			if(!ApproximatelyEqual(p_Lhs.Column(i), p_Rhs.Column(i), p_Tolerance))
			{
				return false;
			}
		}
		return true;
	}

	//===========================================================================
	// Class Definitions
	//===========================================================================

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>::Matrix(const scalar p_Value)
		: m_Page(RealVector<t_Rows>(p_Value))
	{
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const bool Matrix<t_Rows, t_Columns>::operator ==(const Matrix<t_Rows, t_Columns>& p_Rhs) const
	{
		for(u32 i = 0; i < t_Columns; ++i)
		{
			if(Column(i) != p_Rhs.Column(i))
			{
				return false;
			}
		}
		return true;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const bool Matrix<t_Rows, t_Columns>::operator !=(const Matrix<t_Rows, t_Columns>& p_Rhs) const
	{
		return !(*this == p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::Negate()
	{
		m_Page.ApplyFunction([](const Vector<t_Rows>& p_Value)->const Vector<t_Rows>
		{
			return -p_Value;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator -() const
	{
		return Matrix<t_Rows, t_Columns>(*this).Negate();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator +=(const Matrix<t_Rows, t_Columns>& p_Rhs)
	{
		m_Page.Map(p_Rhs.m_Page,
							 [](const RealVector<t_Rows>& p_L, const RealVector<t_Rows>& p_R)->const RealVector<t_Rows>
		{
			return p_L + p_R;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator +(const Matrix<t_Rows, t_Columns>& p_Rhs) const
	{
		return (Matrix<t_Rows, t_Columns>(*this) += p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator -=(const Matrix<t_Rows, t_Columns>& p_Rhs)
	{
		m_Page.Map(p_Rhs.m_Page,
							 [](const RealVector<t_Rows>& p_L, const RealVector<t_Rows>& p_R)->const RealVector<t_Rows>
		{
			return p_L - p_R;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator -(const Matrix<t_Rows, t_Columns>& p_Rhs) const
	{
		return (Matrix<t_Rows, t_Columns>(*this) -= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator *=(const scalar& p_Rhs)
	{
		m_Page.Map([&](const RealVector<t_Rows>& p_Value)->const RealVector<t_Rows>
		{
			return p_Value * p_Rhs;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator *(const scalar p_Rhs) const
	{
		return (Matrix<t_Rows, t_Columns>(*this) *= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::operator /=(const scalar& p_Rhs)
	{
		const scalar denom = Mathematics::Inverse(p_Rhs);

		m_Page.Map([&](const RealVector<t_Rows>& p_Value)->const RealVector<t_Rows>
		{
			return p_Value * denom;
		});

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::operator /(const scalar p_Rhs) const
	{
		return (Matrix<t_Rows, t_Columns>(*this) /= p_Rhs);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	scalar& Matrix<t_Rows, t_Columns>::operator ()(const u32 p_Row, const u32 p_Column)
	{
		return m_Page[p_Column](p_Row);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const scalar Matrix<t_Rows, t_Columns>::operator ()(const u32 p_Row, const u32 p_Column) const
	{
		return m_Page[p_Column](p_Row);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	inline const RealVector<t_Columns> Matrix<t_Rows, t_Columns>::TransposedRow(const u32 p_Row) const
	{
		Assert(p_Row < t_Rows, "Invalid row!");
		const Matrix<t_Rows, t_Columns>& M(*this);
		RealVector<t_Columns> temp;

		for(u32 i = 0; i < t_Columns; ++i)
		{
			temp(i) = M(p_Row, i);
		}

		return temp;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	inline const RealVector<t_Rows> Matrix<t_Rows, t_Columns>::Column(const u32 p_Column) const
	{
		Assert(p_Column < t_Columns, "Invalid column!");
		return m_Page[p_Column];
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	void Matrix<t_Rows, t_Columns>::SetColumn(const u32 p_Column, const RealVector<t_Rows>& p_NewValue)
	{
		m_Page(p_Column) = p_NewValue;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	void Matrix<t_Rows, t_Columns>::SetRow(const u32 p_Row, const RealVector<t_Columns>& p_NewValue)
	{
		for(u32 i = 0; i < t_Columns; ++i)
		{
			m_Page(i)(p_Row) = p_NewValue(i);
		}
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const scalar Matrix<t_Rows, t_Columns>::Determinant() const
	{
		Assert(IsSquare(), "No non-square determinant!");

		//Matrix44 specialize
		//const Matrix<t_Rows, t_Columns>& M(*this);
		//const scalar A = M(3, 3) * M(4, 4) - M(3, 4) * M(4, 3);
		//const scalar B = M(3, 4) * M(4, 2) - M(3, 2) * M(4, 4);
		//const scalar C = M(3, 2) * M(4, 3) - M(3, 3) * M(4, 2);
		//const scalar D = M(3, 1) * M(4, 4) - M(3, 4) * M(4, 1);
		//const scalar E = M(3, 3) * M(4, 1) - M(3, 1) * M(4, 3);
		//const scalar F = M(3, 1) * M(4, 2) - M(3, 2) * M(4, 1);

		//return M(1, 1) * (M(2, 2) * A + M(2, 3) * B + M(2, 4) * C)
		//	+ M(1, 2) * (M(2, 1) * (-A) + M(2, 3) * D + M(2, 4) * E)
		//	+ M(1, 3) * (M(2, 1) * (-B) + M(2, 2) * (-D) + M(2, 4) * F)
		//	+ M(1, 4) * (M(2, 1) * (-C) + M(2, 2) * (-E) + M(2, 3) * (-F));

		//manual LU
		//scalar d = Unity;
		//Matrix<t_Rows, t_Columns> M(*this);

		//for (u32 k = 0; k < t_Columns - 1; ++k)
		//{
		//	//find i >= k where max{M(i,k)}
		//	u32 i(-1);
		//	scalar maxM(NegativeInfinity);
		//	for (u32 testIdx = k; testIdx < t_Rows; ++testIdx)
		//	{
		//		scalar m = AbsoluteValue(M(testIdx, k));
		//		if (m > maxM)
		//		{
		//			i = testIdx;
		//			maxM = m;
		//		}
		//	}

		//	//check for void row or column
		//	if (IsZero(maxM) || IsZero(M(k, k)))
		//	{
		//		return Zero;
		//	}

		//	//pivot if needed
		//	if (k != i)
		//	{
		//		M.SwitchRows(i, k);
		//		d = -d;
		//	}

		//	//clear entries below (k,k)
		//	for (u32 r = k + 1; r < t_Rows; ++r)
		//	{
		//		scalar rowScale = -M(r, k) / M(k, k);
		//		M.AddScaledRowToRow(r, k, rowScale);
		//	}
		//}

		////get the diagonals of the upper triangular matrix
		//RealVector<t_Columns> diag(M.Diagonal());
		//for (u32 i = 0; i < t_Columns; ++i)
		//{
		//	d *= diag(i);
		//}

		////return determinant
		//return d;

		MatrixDecomposition<t_Rows> decomp(*this);
		return decomp.Determinant();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const RealVector<t_Rows> Matrix<t_Rows, t_Columns>::Diagonal() const
	{
		Assert(IsSquare(), "Not square, no diagonal!");

		RealVector<t_Rows> temp(Zero);
		for(u32 i = 0; i < t_Rows; ++i)
		{
			temp(i) = (*this)(i, i);
		}

		return temp;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const scalar Matrix<t_Rows, t_Columns>::Trace() const
	{
		Assert(IsSquare(), "Not square, no trace!");
		scalar sum(Zero);
		RealVector<t_Rows> temp(Diagonal());
		for(u32 i = 0; i < t_Rows; ++i)
		{
			sum += temp(i);
		}

		return sum;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const scalar Matrix<t_Rows, t_Columns>::Cofactor(const u32 p_Row, const u32 p_Column) const
	{
		return (((p_Row + p_Column) % 2 == 0) ? (1) : (-1)) * Minor(p_Row, p_Column);
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::Adjucation() const
	{
		Assert(IsSquare(), "Not square, no adjucate!");
		Matrix<t_Rows, t_Columns> Cofactors;
		for(u32 r = 0; r < t_Rows; ++r)
		{
			for(u32 c = 0; c < t_Columns; ++c)
			{
				Cofactors(r, c) = Cofactor(r, c);
			}
		}

		return Cofactors.Transposition();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows, t_Columns> Matrix<t_Rows, t_Columns>::Inverse() const
	{
		//B.N: NAIVE!! Inverse() = Adjucation() / Determinant();

		//Matrix44 specialized

		//const scalar D = Determinant();
		//const Matrix<t_Rows, t_Columns>& M(*this);
		//const scalar T = M.Trace();
		//const Matrix<t_Rows, t_Columns> M2 = M * M;
		//const scalar T2 = M2.Trace();
		//const Matrix<t_Rows, t_Columns> M3 = M * M2;

		//return (ConstantMatrices::Identity * ((T*T*T - 3 * T*T2 + 2 * M3.Trace()) / 6)
		//	- (M * ((T*T - T2) / 2))
		//	+ (M2 * T)
		//	- M3) / D;

		Assert(IsSquare(), "Not square, cannot get an inverse!");
		//Assert(!IsSingular(), "Singular! Cannot get an inverse!");

		////construct work matrices
		//Matrix<t_Rows, t_Columns> LM(*this);
		//Matrix<t_Rows, t_Columns> RM(In<t_Rows>());

		//for (u32 j = 0; j < t_Columns; ++j)
		//{
		//	//find i >= k where max{LM(i,k)}
		//	u32 i(-1);
		//	scalar maxLM(NegativeInfinity);
		//	for (u32 testIdx = j; testIdx < t_Rows; ++testIdx)
		//	{
		//		scalar lm = AbsoluteValue(LM(testIdx, j));
		//		if (lm > maxLM)
		//		{
		//			i = testIdx;
		//			maxLM = lm;
		//		}
		//	}

		//	//pivot if needed
		//	if (j != i)
		//	{
		//		LM.SwitchRows(i, j);
		//		RM.SwitchRows(i, j);
		//	}

		//	//scale pivot to 1
		//	scalar rowScale(Unity / LM(j, j));
		//	LM.ScaleRow(j, rowScale);
		//	RM.ScaleRow(j, rowScale);

		//	//clear entries above (j,j)
		//	for (u32 r = 0; r < j; ++r)
		//	{
		//		rowScale = -LM(r, j);
		//		LM.AddScaledRowToRow(r, j, rowScale);
		//		RM.AddScaledRowToRow(r, j, rowScale);
		//	}

		//	//clear entries below (j,j)
		//	for (u32 r = j + 1; r < t_Rows; ++r)
		//	{
		//		rowScale = -LM(r, j);
		//		LM.AddScaledRowToRow(r, j, rowScale);
		//		RM.AddScaledRowToRow(r, j, rowScale);
		//	}
		//}

		////RM is now the inverse
		//return RM;

		MatrixDecomposition<t_Rows> decomp(*this);
		Assert(!decomp.IsSingular(), "No inverse exists!");
		Matrix<t_Rows, t_Columns> inv;
		decomp.Inverse(inv);
		return inv;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::Invert()
	{
		*this = this->Inverse();
		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Columns, t_Rows> Matrix<t_Rows, t_Columns>::Transposition() const
	{
		//Matrix44 specialized
		//const Matrix<t_Rows, t_Columns>& M(*this);
		//return Matrix<t_Rows, t_Columns>(M(1, 1), M(2, 1), M(3, 1), M(4, 1)
		//	, M(1, 2), M(2, 2), M(3, 2), M(4, 2)
		//	, M(1, 3), M(2, 3), M(3, 3), M(4, 3)
		//	, M(1, 4), M(2, 4), M(3, 4), M(4, 4));

		Matrix<t_Columns, t_Rows> temp;
		for(u32 i = 0; i < t_Rows; ++i)
		{
			for(u32 j = 0; j < t_Columns; ++j)
			{
				temp(j, i) = (*this)(i, j);
			}
		}
		return temp;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Columns, t_Rows>& Matrix<t_Rows, t_Columns>::Transpose()
	{
		*this = this->Transposition();
		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Columns, t_Rows> Matrix<t_Rows, t_Columns>::InverseTransposition() const
	{
		Matrix<t_Columns, t_Rows> temp;
		return Matrix<t_Columns, t_Rows>(*this).InverseTranspose();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Columns, t_Rows>& Matrix<t_Rows, t_Columns>::InverseTranspose()
	{
		(*this).Invert().Transpose();
		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const scalar Matrix<t_Rows, t_Columns>::NormSquared() const
	{
		const Matrix<t_Rows, t_Columns>& M(*this);
		return (M.Transposition() * M).Trace();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const scalar Matrix<t_Rows, t_Columns>::Norm() const
	{
		return std::sqrt(NormSquared());
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	bool Matrix<t_Rows, t_Columns>::IsSquare() const
	{
		return t_Rows == t_Columns;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	inline bool Matrix<t_Rows, t_Columns>::IsSingular() const
	{
		return !IsSquare() || (IsSquare() && IsZero(Determinant()));
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	bool Matrix<t_Rows, t_Columns>::IsOrthogonal() const
	{
		return !IsSingular() && (*this).Inverse() == (*this).Transposition();
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	bool Matrix<t_Rows, t_Columns>::IsSpecialOrthogonal() const
	{
		return IsOrthogonal() && (IsUnity(Determinant()));
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::SwitchRows(const u32 p_Row1, const u32 p_Row2)
	{
		Assert(p_Row1 != p_Row2, "Cannot switch a row with itself");
		Matrix<t_Rows, t_Columns>& M(*this);
		scalar temp(0.0f);
		for(u32 c = 0; c < t_Columns; ++c)
		{
			temp = M(p_Row1, c);
			M(p_Row1, c) = M(p_Row2, c);
			M(p_Row2, c) = temp;
		}

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::ScaleRow(const u32 p_Row, const scalar p_Scalar)
	{
		Matrix<t_Rows, t_Columns>& M(*this);
		for(u32 c = 0; c < t_Columns; ++c)
		{
			scalar& rowElem(M(p_Row, c));
			rowElem = p_Scalar * M(p_Row, c);
			rowElem = (IsApproximatelyZero(rowElem, 0.00001f)) ? (Zero) : (rowElem);

		}

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	Matrix<t_Rows, t_Columns>& Matrix<t_Rows, t_Columns>::AddScaledRowToRow(const u32 p_Row, const u32 p_ScaledRow, const scalar p_Scalar)
	{
		Assert(p_Row != p_ScaledRow, "Cannot scale a row with itself.");
		Matrix<t_Rows, t_Columns>& M(*this);
		for(u32 c = 0; c < t_Columns; ++c)
		{
			scalar& rowElem(M(p_Row, c));
			rowElem += p_Scalar * M(p_ScaledRow, c);
			rowElem = (IsApproximatelyZero(rowElem, 0.00001f)) ? (Zero) : (rowElem);
		}

		return *this;
	}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const Matrix<t_Rows - 1, t_Columns - 1>
		Matrix<t_Rows, t_Columns>::Submatrix(const u32 p_RemovedRow
		, const u32 p_RemovedColumn) const
	{
			const Matrix<t_Rows, t_Columns>& M(*this);
			Matrix<t_Rows - 1, t_Columns - 1> sub;

			for(u32 r = 0; r < p_RemovedRow; ++r)
			{
				for(u32 c = 0; c < p_RemovedColumn; ++c)
				{
					sub(r, c) = M(r, c);
				}

				for(u32 c = p_RemovedColumn + 1; c < t_Columns; ++c)
				{
					sub(r, c) = M(r, c);
				}
			}

			for(u32 r = p_RemovedRow + 1; r < t_Rows; ++r)
			{
				for(u32 c = 0; c < p_RemovedColumn; ++c)
				{
					sub(r, c) = M(r, c);
				}

				for(u32 c = p_RemovedColumn + 1; c < t_Columns; ++c)
				{
					sub(r, c) = M(r, c);
				}
			}

			return sub;
		}

	//---------------------------------------------------------------------------

	template <u32 t_Rows, u32 t_Columns>
	const scalar Matrix<t_Rows, t_Columns>::Minor(const u32 p_RemovedRow, const u32 p_RemovedColumn) const
	{
		return Submatrix(p_RemovedRow, p_RemovedColumn).Determinant();
	}

} // namespace Mathematics
