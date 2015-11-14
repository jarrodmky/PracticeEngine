#ifndef IncludedVisuLinearColourH
#define IncludedVisuLinearColourH

//===========================================================================
// Filename:	LinearColour.h
// Author:		Jarrod MacKay
// Description:	Holds a coordinate in RGBA colour system.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

//===========================================================================
// Definitions
//===========================================================================

namespace Visualization
{
	class LinearColour
	{
	//Attributes
	public:

		f32 R;
		f32 G;
		f32 B;
		f32 A;

	//Operators
	public:

		LinearColour(f32 p_Red, f32 p_Green, f32 Blue, f32 Alpha);

		LinearColour(const u32 p_HexRGB);

		LinearColour& operator +=(const LinearColour& p_Other);

		LinearColour operator +(const LinearColour& p_Other) const;

		LinearColour& operator *=(const LinearColour& p_Other);

		LinearColour operator*(const LinearColour& p_Other) const;

		LinearColour operator*(const f32 p_Scalar) const;

		friend LinearColour operator*(const f32 p_Scalar, const LinearColour& p_Other);

	private:

		void LinearColour::Clamp();
	};

	namespace ConstantColours
	{
		const static LinearColour AliceBlue(0xF0F8FF);
		const static LinearColour AntiqueWhite(0xFAEBD7);
		const static LinearColour Aqua(0x00FFFF);
		const static LinearColour Aquamarine(0x7FFFD4);
		const static LinearColour Azure(0xF0FFFF);
		const static LinearColour Beige(0xF5F5DC);
		const static LinearColour Bisque(0xFFE4C4);
		const static LinearColour Black(0x000000);
		const static LinearColour BlanchedAlmond(0xFFEBCD);
		const static LinearColour Blue(0x0000FF);
		const static LinearColour BlueViolet(0x8A2BE2);
		const static LinearColour Brown(0xA52A2A);
		const static LinearColour BurlyWood(0xDEB887);
		const static LinearColour CadetBlue(0x5F9EA0);
		const static LinearColour Chartreuse(0x7FFF00);
		const static LinearColour Chocolate(0xD2691E);
		const static LinearColour Coral(0xFF7F50);
		const static LinearColour CornflowerBlue(0x6495ED);
		const static LinearColour Cornsilk(0xFFF8DC);
		const static LinearColour Crimson(0xDC143C);
		const static LinearColour Cyan(0x00FFFF);
		const static LinearColour DarkBlue(0x00008B);
		const static LinearColour DarkCyan(0x008B8B);
		const static LinearColour DarkGoldenRod(0xB8860B);
		const static LinearColour DarkGray(0xA9A9A9);
		const static LinearColour DarkGreen(0x006400);
		const static LinearColour DarkKhaki(0xBDB76B);
		const static LinearColour DarkMagenta(0x8B008B);
		const static LinearColour DarkOliveGreen(0x556B2F);
		const static LinearColour DarkOrange(0xFF8C00);
		const static LinearColour DarkOrchid(0x9932CC);
		const static LinearColour DarkRed(0x8B0000);
		const static LinearColour DarkSalmon(0xE9967A);
		const static LinearColour DarkSeaGreen(0x8FBC8F);
		const static LinearColour DarkSlateBlue(0x483D8B);
		const static LinearColour DarkSlateGray(0x2F4F4F);
		const static LinearColour DarkTurquoise(0x00CED1);
		const static LinearColour DarkViolet(0x9400D3);
		const static LinearColour DeepPink(0xFF1493);
		const static LinearColour DeepSkyBlue(0x00BFFF);
		const static LinearColour DimGray(0x696969);
		const static LinearColour DodgerBlue(0x1E90FF);
		const static LinearColour FireBrick(0xB22222);
		const static LinearColour FloralWhite(0xFFFAF0);
		const static LinearColour ForestGreen(0x228B22);
		const static LinearColour Fuchsia(0xFF00FF);
		const static LinearColour Gainsboro(0xDCDCDC);
		const static LinearColour GhostWhite(0xF8F8FF);
		const static LinearColour Gold(0xFFD700);
		const static LinearColour GoldenRod(0xDAA520);
		const static LinearColour Gray(0x808080);
		const static LinearColour Green(0x008000);
		const static LinearColour GreenYellow(0xADFF2F);
		const static LinearColour HoneyDew(0xF0FFF0);
		const static LinearColour HotPink(0xFF69B4);
		const static LinearColour IndianRed(0xCD5C5C);
		const static LinearColour Indigo(0x4B0082);
		const static LinearColour Ivory(0xFFFFF0);
		const static LinearColour Khaki(0xF0E68C);
		const static LinearColour Lavender(0xE6E6FA);
		const static LinearColour LavenderBlush(0xFFF0F5);
		const static LinearColour LawnGreen(0x7CFC00);
		const static LinearColour LemonChiffon(0xFFFACD);
		const static LinearColour LightBlue(0xADD8E6);
		const static LinearColour LightCoral(0xF08080);
		const static LinearColour LightCyan(0xE0FFFF);
		const static LinearColour LightGoldenRodYellow(0xFAFAD2);
		const static LinearColour LightGray(0xD3D3D3);
		const static LinearColour LightGreen(0x90EE90);
		const static LinearColour LightPink(0xFFB6C1);
		const static LinearColour LightSalmon(0xFFA07A);
		const static LinearColour LightSeaGreen(0x20B2AA);
		const static LinearColour LightSkyBlue(0x87CEFA);
		const static LinearColour LightSlateGray(0x778899);
		const static LinearColour LightSteelBlue(0xB0C4DE);
		const static LinearColour LightYellow 	(0xFFFFE0);
		const static LinearColour Lime(0x00FF00);
		const static LinearColour LimeGreen(0x32CD32);
		const static LinearColour Linen(0xFAF0E6);
		const static LinearColour Magenta(0xFF00FF);
		const static LinearColour Maroon(0x800000);
		const static LinearColour MediumAquaMarine(0x66CDAA);
		const static LinearColour MediumBlue(0x0000CD);
		const static LinearColour MediumOrchid(0xBA55D3);
		const static LinearColour MediumPurple(0x9370DB);
		const static LinearColour MediumSeaGreen(0x3CB371);
		const static LinearColour MediumSlateBlue(0x7B68EE);
		const static LinearColour MediumSpringGreen(0x00FA9A);
		const static LinearColour MediumTurquoise(0x48D1CC);
		const static LinearColour MediumVioletRed(0xC71585);
		const static LinearColour MidnightBlue(0x191970);
		const static LinearColour MintCream(0xF5FFFA);
		const static LinearColour MistyRose(0xFFE4E1);
		const static LinearColour Moccasin(0xFFE4B5);
		const static LinearColour NavajoWhite(0xFFDEAD);
		const static LinearColour Navy(0x000080);
		const static LinearColour OldLace(0xFDF5E6);
		const static LinearColour Olive(0x808000);
		const static LinearColour OliveDrab(0x6B8E23);
		const static LinearColour Orange(0xFFA500);
		const static LinearColour OrangeRed(0xFF4500);
		const static LinearColour Orchid(0xDA70D6);
		const static LinearColour PaleGoldenRod(0xEEE8AA);
		const static LinearColour PaleGreen(0x98FB98);
		const static LinearColour PaleTurquoise(0xAFEEEE);
		const static LinearColour PaleVioletRed(0xDB7093);
		const static LinearColour PapayaWhip(0xFFEFD5);
		const static LinearColour PeachPuff(0xFFDAB9);
		const static LinearColour Peru(0xCD853F);
		const static LinearColour Pink(0xFFC0CB);
		const static LinearColour Plum(0xDDA0DD);
		const static LinearColour PowderBlue(0xB0E0E6);
		const static LinearColour Purple(0x800080);
		const static LinearColour RebeccaPurple(0x663399);
		const static LinearColour Red(0xFF0000);
		const static LinearColour RosyBrown(0xBC8F8F);
		const static LinearColour RoyalBlue(0x4169E1);
		const static LinearColour SaddleBrown(0x8B4513);
		const static LinearColour Salmon(0xFA8072);
		const static LinearColour SandyBrown(0xF4A460);
		const static LinearColour SeaGreen(0x2E8B57);
		const static LinearColour SeaShell(0xFFF5EE);
		const static LinearColour Sienna(0xA0522D);
		const static LinearColour Silver(0xC0C0C0);
		const static LinearColour SkyBlue(0x87CEEB);
		const static LinearColour SlateBlue(0x6A5ACD);
		const static LinearColour SlateGray(0x708090);
		const static LinearColour Snow(0xFFFAFA);
		const static LinearColour SpringGreen(0x00FF7F);
		const static LinearColour SteelBlue(0x4682B4);
		const static LinearColour Tan(0xD2B48C);
		const static LinearColour Teal(0x008080);
		const static LinearColour Thistle(0xD8BFD8);
		const static LinearColour Tomato(0xFF6347);
		const static LinearColour Turquoise(0x40E0D0);
		const static LinearColour Violet(0xEE82EE);
		const static LinearColour Wheat(0xF5DEB3);
		const static LinearColour White(0xFFFFFF);
		const static LinearColour WhiteSmoke(0xF5F5F5);
		const static LinearColour Yellow(0xFFFF00);
		const static LinearColour YellowGreen(0x9ACD32);
	}
} // namespace Visualization

#endif // #ifdef IncludedVisuLinearColourH