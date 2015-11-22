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

		LinearColour(const u32 p_HexRGB = 0);

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
		const LinearColour AliceBlue(0xF0F8FF);
		const LinearColour AntiqueWhite(0xFAEBD7);
		const LinearColour Aqua(0x00FFFF);
		const LinearColour Aquamarine(0x7FFFD4);
		const LinearColour Azure(0xF0FFFF);
		const LinearColour Beige(0xF5F5DC);
		const LinearColour Bisque(0xFFE4C4);
		const LinearColour Black(0x000000);
		const LinearColour BlanchedAlmond(0xFFEBCD);
		const LinearColour Blue(0x0000FF);
		const LinearColour BlueViolet(0x8A2BE2);
		const LinearColour Brown(0xA52A2A);
		const LinearColour BurlyWood(0xDEB887);
		const LinearColour CadetBlue(0x5F9EA0);
		const LinearColour Chartreuse(0x7FFF00);
		const LinearColour Chocolate(0xD2691E);
		const LinearColour Coral(0xFF7F50);
		const LinearColour CornflowerBlue(0x6495ED);
		const LinearColour Cornsilk(0xFFF8DC);
		const LinearColour Crimson(0xDC143C);
		const LinearColour Cyan(0x00FFFF);
		const LinearColour DarkBlue(0x00008B);
		const LinearColour DarkCyan(0x008B8B);
		const LinearColour DarkGoldenRod(0xB8860B);
		const LinearColour DarkGray(0xA9A9A9);
		const LinearColour DarkGreen(0x006400);
		const LinearColour DarkKhaki(0xBDB76B);
		const LinearColour DarkMagenta(0x8B008B);
		const LinearColour DarkOliveGreen(0x556B2F);
		const LinearColour DarkOrange(0xFF8C00);
		const LinearColour DarkOrchid(0x9932CC);
		const LinearColour DarkRed(0x8B0000);
		const LinearColour DarkSalmon(0xE9967A);
		const LinearColour DarkSeaGreen(0x8FBC8F);
		const LinearColour DarkSlateBlue(0x483D8B);
		const LinearColour DarkSlateGray(0x2F4F4F);
		const LinearColour DarkTurquoise(0x00CED1);
		const LinearColour DarkViolet(0x9400D3);
		const LinearColour DeepPink(0xFF1493);
		const LinearColour DeepSkyBlue(0x00BFFF);
		const LinearColour DimGray(0x696969);
		const LinearColour DodgerBlue(0x1E90FF);
		const LinearColour FireBrick(0xB22222);
		const LinearColour FloralWhite(0xFFFAF0);
		const LinearColour ForestGreen(0x228B22);
		const LinearColour Fuchsia(0xFF00FF);
		const LinearColour Gainsboro(0xDCDCDC);
		const LinearColour GhostWhite(0xF8F8FF);
		const LinearColour Gold(0xFFD700);
		const LinearColour GoldenRod(0xDAA520);
		const LinearColour Gray(0x808080);
		const LinearColour Green(0x008000);
		const LinearColour GreenYellow(0xADFF2F);
		const LinearColour HoneyDew(0xF0FFF0);
		const LinearColour HotPink(0xFF69B4);
		const LinearColour IndianRed(0xCD5C5C);
		const LinearColour Indigo(0x4B0082);
		const LinearColour Ivory(0xFFFFF0);
		const LinearColour Khaki(0xF0E68C);
		const LinearColour Lavender(0xE6E6FA);
		const LinearColour LavenderBlush(0xFFF0F5);
		const LinearColour LawnGreen(0x7CFC00);
		const LinearColour LemonChiffon(0xFFFACD);
		const LinearColour LightBlue(0xADD8E6);
		const LinearColour LightCoral(0xF08080);
		const LinearColour LightCyan(0xE0FFFF);
		const LinearColour LightGoldenRodYellow(0xFAFAD2);
		const LinearColour LightGray(0xD3D3D3);
		const LinearColour LightGreen(0x90EE90);
		const LinearColour LightPink(0xFFB6C1);
		const LinearColour LightSalmon(0xFFA07A);
		const LinearColour LightSeaGreen(0x20B2AA);
		const LinearColour LightSkyBlue(0x87CEFA);
		const LinearColour LightSlateGray(0x778899);
		const LinearColour LightSteelBlue(0xB0C4DE);
		const LinearColour LightYellow 	(0xFFFFE0);
		const LinearColour Lime(0x00FF00);
		const LinearColour LimeGreen(0x32CD32);
		const LinearColour Linen(0xFAF0E6);
		const LinearColour Magenta(0xFF00FF);
		const LinearColour Maroon(0x800000);
		const LinearColour MediumAquaMarine(0x66CDAA);
		const LinearColour MediumBlue(0x0000CD);
		const LinearColour MediumOrchid(0xBA55D3);
		const LinearColour MediumPurple(0x9370DB);
		const LinearColour MediumSeaGreen(0x3CB371);
		const LinearColour MediumSlateBlue(0x7B68EE);
		const LinearColour MediumSpringGreen(0x00FA9A);
		const LinearColour MediumTurquoise(0x48D1CC);
		const LinearColour MediumVioletRed(0xC71585);
		const LinearColour MidnightBlue(0x191970);
		const LinearColour MintCream(0xF5FFFA);
		const LinearColour MistyRose(0xFFE4E1);
		const LinearColour Moccasin(0xFFE4B5);
		const LinearColour NavajoWhite(0xFFDEAD);
		const LinearColour Navy(0x000080);
		const LinearColour OldLace(0xFDF5E6);
		const LinearColour Olive(0x808000);
		const LinearColour OliveDrab(0x6B8E23);
		const LinearColour Orange(0xFFA500);
		const LinearColour OrangeRed(0xFF4500);
		const LinearColour Orchid(0xDA70D6);
		const LinearColour PaleGoldenRod(0xEEE8AA);
		const LinearColour PaleGreen(0x98FB98);
		const LinearColour PaleTurquoise(0xAFEEEE);
		const LinearColour PaleVioletRed(0xDB7093);
		const LinearColour PapayaWhip(0xFFEFD5);
		const LinearColour PeachPuff(0xFFDAB9);
		const LinearColour Peru(0xCD853F);
		const LinearColour Pink(0xFFC0CB);
		const LinearColour Plum(0xDDA0DD);
		const LinearColour PowderBlue(0xB0E0E6);
		const LinearColour Purple(0x800080);
		const LinearColour RebeccaPurple(0x663399);
		const LinearColour Red(0xFF0000);
		const LinearColour RosyBrown(0xBC8F8F);
		const LinearColour RoyalBlue(0x4169E1);
		const LinearColour SaddleBrown(0x8B4513);
		const LinearColour Salmon(0xFA8072);
		const LinearColour SandyBrown(0xF4A460);
		const LinearColour SeaGreen(0x2E8B57);
		const LinearColour SeaShell(0xFFF5EE);
		const LinearColour Sienna(0xA0522D);
		const LinearColour Silver(0xC0C0C0);
		const LinearColour SkyBlue(0x87CEEB);
		const LinearColour SlateBlue(0x6A5ACD);
		const LinearColour SlateGray(0x708090);
		const LinearColour Snow(0xFFFAFA);
		const LinearColour SpringGreen(0x00FF7F);
		const LinearColour SteelBlue(0x4682B4);
		const LinearColour Tan(0xD2B48C);
		const LinearColour Teal(0x008080);
		const LinearColour Thistle(0xD8BFD8);
		const LinearColour Tomato(0xFF6347);
		const LinearColour Turquoise(0x40E0D0);
		const LinearColour Violet(0xEE82EE);
		const LinearColour Wheat(0xF5DEB3);
		const LinearColour White(0xFFFFFF);
		const LinearColour WhiteSmoke(0xF5F5F5);
		const LinearColour Yellow(0xFFFF00);
		const LinearColour YellowGreen(0x9ACD32);
	}
} // namespace Visualization

#endif // #ifdef IncludedVisuLinearColourH