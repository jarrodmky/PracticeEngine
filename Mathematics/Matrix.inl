Mathematics::Matrix::Matrix(const scalar p_Value)
: m_Array(p_Value)
{}

Mathematics::Matrix::Matrix(const Vector p_FirstAxis
						  , const Vector p_SecondAxis
						  , const Vector p_ThirdAxis
						  , const Point p_Origin)
: m_Array()
{
	//first column
	m_Array(1, 1) = p_FirstAxis.x;
	m_Array(2, 1) = p_FirstAxis.y;
	m_Array(3, 1) = p_FirstAxis.z;
	
	//second column
	m_Array(1, 2) = p_SecondAxis.x;
	m_Array(2, 2) = p_SecondAxis.y;
	m_Array(3, 2) = p_SecondAxis.z;

	//third column
	m_Array(1, 3) = p_ThirdAxis.x;
	m_Array(2, 3) = p_ThirdAxis.y;
	m_Array(3, 3) = p_ThirdAxis.z;

	//fourth column
	m_Array(1, 4) = p_Origin.x;
	m_Array(2, 4) = p_Origin.y;
	m_Array(3, 4) = p_Origin.z;
	m_Array(4, 4) = ConstantScalars::Unity;
}