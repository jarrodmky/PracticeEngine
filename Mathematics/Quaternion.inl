Mathematics::Quaternion::Quaternion(const scalar p_Value)
: m_Real(p_Value), m_Imaginary(p_Value)
{}

Mathematics::Quaternion::Quaternion(const Vector& p_Axis, const scalar p_Angle)
: m_Real(std::sin(p_Angle * 0.5f))
, m_Imaginary(p_Axis.x, p_Axis.y, p_Axis.z)
{
	m_Imaginary.Normalize();
	m_Imaginary += std::cos(p_Angle * 0.5f);
}