//===========================================================================
// Filename:	SpecificConstraint.inl
// Author:		Jarrod MacKay
// Date:		16/03/2016
//===========================================================================

//===========================================================================
// Definitions
//===========================================================================

template <u32 t_Dimensions>
class Stick : public Constraint<t_Dimensions, 2>
{
protected: //Attributes

	scalar m_Length;

public:	//Operators

	Stick(VerletParticle<t_Dimensions>& p_ParticleA
		, VerletParticle<t_Dimensions>& p_ParticleB
		, const scalar p_Length)
		: Constraint<t_Dimensions, 2>(p_ParticleA, p_ParticleB)
		, m_Length(p_Length)
	{
		Assert(p_Length > Zero, "Non-zero length!");
	}

	//virtuals
	virtual ~Stick() {}
	virtual void Relax(scalar p_DeltaTime) override = 0
	{
		//force particles to certain length
		RealVector<t_Dimensions> displacement = m_ParticleB.Position - m_ParticleA.Position;
		const scalar actualDistance = displacement.Length();
		RealVector<t_Dimensions> halfDeltaDisplacement = (((actualDistance - m_Length) / actualDistance) * 0.5f) * displacement;
		m_ParticleA.Position += halfDeltaDisplacement;
		m_ParticleB.Position -= halfDeltaDisplacement;
	}
};