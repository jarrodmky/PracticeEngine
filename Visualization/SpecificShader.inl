//===========================================================================
// Filename:	ShaderSpecializations.inl
// Author:		Jarrod MacKay
//===========================================================================

//==========
// Flat Shaders
//==========

class DrawnVertexShader : public VertexShader<FlatVertex>
{
//Methods
public:

	DrawnVertexShader(System& p_System)
	: VertexShader<FlatVertex>(p_System, L"../Data/Shaders/FlatDrawing.fx")
	{}

	virtual ~DrawnVertexShader() {}
};

class DrawnPixelShader : public PixelShader
{
//Methods
public:

	DrawnPixelShader(System& p_System)
	: PixelShader(p_System, L"../Data/Shaders/FlatDrawing.fx")
	{}

	virtual ~DrawnPixelShader() {}
};

//==========
// Lit Shaders
//==========

class LitVertexShader : public VertexShader<LitVertex>
{
//Methods
public:

	LitVertexShader(System& p_System)
	: VertexShader<LitVertex>(p_System, L"../Data/Shaders/LitShading.fx")
	{}

	virtual ~LitVertexShader() {}
};

class LitPixelShader : public PixelShader
{
//Methods
public:

	LitPixelShader(System& p_System)
	: PixelShader(p_System, L"../Data/Shaders/LitShading.fx")
	{}

	virtual ~LitPixelShader() {}
};

//==========
// Painted Shaders
//==========

class PostProcessVertexShader : public VertexShader<PaintedVertex>
{
	//Methods
public:

	PostProcessVertexShader(System& p_System)
		: VertexShader<PaintedVertex>(p_System, L"../Data/Shaders/PaintPostProcess.fx")
	{}

	virtual ~PostProcessVertexShader() {}
};

class PostProcessPixelShader : public PixelShader
{
	//Methods
public:

	PostProcessPixelShader(System& p_System)
		: PixelShader(p_System, L"../Data/Shaders/PaintPostProcess.fx")
	{}

	virtual ~PostProcessPixelShader() {}
};

//==========
// Surface Shaders
//==========

class WaterVertexShader : public VertexShader<SurfaceVertex>
{
	//Methods
public:

	WaterVertexShader(System& p_System)
		: VertexShader<SurfaceVertex>(p_System, L"../Data/Shaders/WaterShading.fx")
	{}

	virtual ~WaterVertexShader() {}
};

class WaterDepthMapping : public VertexShader<SurfaceVertex>
{
	//Methods
public:

	WaterDepthMapping(System& p_System)
		: VertexShader<SurfaceVertex>(p_System, L"../Data/Shaders/WaterDepthMapping.fx")
	{}

	virtual ~WaterDepthMapping() {}
};

class WaterPixelShader : public PixelShader
{
	//Methods
public:

	WaterPixelShader(System& p_System)
		: PixelShader(p_System, L"../Data/Shaders/WaterShading.fx")
	{}

	virtual ~WaterPixelShader() {}
};

//==========
// Frame Shaders
//==========

class FrameVertexShader : public VertexShader<FramedVertex>
{
//Methods
public:

	FrameVertexShader(System& p_System)
	: VertexShader<FramedVertex>(p_System, L"../Data/Shaders/FrameShading.fx")
	{}

	virtual ~FrameVertexShader() {}
};

class FrameDepthMapping : public VertexShader<FramedVertex>
{
	//Methods
public:

	FrameDepthMapping(System& p_System)
		: VertexShader<FramedVertex>(p_System, L"../Data/Shaders/FrameDepthMapping.fx")
	{}

	virtual ~FrameDepthMapping() {}
};

class FramePixelShader : public PixelShader
{
//Methods
public:

	FramePixelShader(System& p_System)
	: PixelShader(p_System, L"../Data/Shaders/FrameShading.fx")
	{}

	virtual ~FramePixelShader() {}
};

class FrameFancyPixelShader : public PixelShader
{
//Methods
public:

	FrameFancyPixelShader(System& p_System)
	: PixelShader(p_System, L"../Data/Shaders/FrameFancyShading.fx")
	{}

	virtual ~FrameFancyPixelShader() {}
};

class FrameCelPixelShader : public PixelShader
{
//Methods
public:

	FrameCelPixelShader(System& p_System)
		: PixelShader(p_System, L"../Data/Shaders/FrameCelShading.fx")
	{}

	virtual ~FrameCelPixelShader() {}
};