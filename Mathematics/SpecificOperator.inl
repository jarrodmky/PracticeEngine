//===========================================================================
// Filename:	SpecificOperator.inl
// Author:		Jarrod MacKay
// Date:		16/03/2016
//===========================================================================

//===========================================================================
// Definitions
//===========================================================================

template <u32 t_Dimensions>
class ProjectFromSphere : public Operator<t_Dimensions, 1>
{
protected: //Attributes

	scalar m_Radius;

public:	//Operators

	explicit ProjectFromSphere(const VerletParticle<t_Dimensions>& p_Particle)
		: Operator<t_Dimensions, 1>(p_Particle) {}

	//virtuals
	virtual ~ProjectFromSphere() {}
	virtual void Operate(const VerletParticle<t_Dimensions>& p_Particle) override = 0
	{
	}
};