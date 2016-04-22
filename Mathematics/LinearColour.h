#ifndef IncludedMathLinearColourH
#define IncludedMathLinearColourH

//===========================================================================
// Filename:	LinearColour.h
// Author:		Jarrod MacKay
// Description:	Holds a coordinate in RGBA colour system.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "MathBase.h"
#include "Vector.h"

//===========================================================================
// Definitions
//===========================================================================

namespace Mathematics
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

		explicit LinearColour(f32 p_Red, f32 p_Green, f32 Blue, f32 Alpha);

		explicit LinearColour(const u32 p_HexRGB = 0);

		LinearColour& operator +=(const LinearColour& p_Other);

		LinearColour operator +(const LinearColour& p_Other) const;

		LinearColour& operator *=(const LinearColour& p_Other);

		LinearColour operator*(const LinearColour& p_Other) const;

		LinearColour& operator *=(const f32 p_Scalar);

		LinearColour operator*(const f32 p_Scalar) const;

		friend LinearColour operator*(const f32 p_Scalar, const LinearColour& p_Other);

		void Clamp();

		inline LinearColour& SetAlpha(const scalar p_Alpha)
		{
			Assert(IsInInterval(p_Alpha, Zero, Unity), "Invalid alpha value!");
			A = p_Alpha;
		}

		inline LinearColour SetAlpha(const scalar p_Alpha) const
		{
			Assert(IsInInterval(p_Alpha, Zero, Unity), "Invalid alpha value!");
			LinearColour temp(*this);
			temp.A = p_Alpha;
			return temp;
		}
	};

	//functions
	//colour pallet

	namespace ColourPallet
	{
		//http://www.color-hex.com/color-names.html

		const LinearColour AliceBlue(0xf0f8ff);
		const LinearColour AntiqueWhite(0xfaebd7);
		const LinearColour AntiqueWhite2(0xffefdb);
		const LinearColour AntiqueWhite3(0xeedfcc);
		const LinearColour AntiqueWhite4(0xcdc0b0);
		const LinearColour AntiqueWhite5(0x8b8378);
		const LinearColour Aquamarine(0x7fffd4);
		const LinearColour Aquamarine2(0x76eec6);
		const LinearColour Aquamarine3(0x458b74);
		const LinearColour Azure(0xf0ffff);
		const LinearColour Azure2(0xe0eeee);
		const LinearColour Azure3(0xc1cdcd);
		const LinearColour Azure4(0x838b8b);
		const LinearColour Beige(0xf5f5dc);
		const LinearColour Bisque(0xffe4c4);
		const LinearColour Bisque2(0xeed5b7);
		const LinearColour Bisque3(0xcdb79e);
		const LinearColour Bisque4(0x8b7d6b);
		const LinearColour Black(0x000000);
		const LinearColour BlanchedAlmond(0xffebcd);
		const LinearColour Blue(0x0000ff);
		const LinearColour Blue2(0x0000ee);
		const LinearColour Blue3(0x0000c5);
		const LinearColour Blue4(0x00008b);
		const LinearColour BlueViolet(0x8a2be2);
		const LinearColour Brown(0xa52a2a);
		const LinearColour Brown2(0xff4040);
		const LinearColour Brown3(0xee3b3b);
		const LinearColour Brown4(0xcd3333);
		const LinearColour Brown5(0x8b2323);
		const LinearColour Burlywood(0xdeb887);
		const LinearColour Burlywood2(0xffd39b);
		const LinearColour Burlywood3(0xeec591);
		const LinearColour Burlywood4(0xcdaa7d);
		const LinearColour Burlywood5(0x8b7355);
		const LinearColour CadetBlue(0x5f9ea0);
		const LinearColour CadetBlue2(0x98f5ff);
		const LinearColour CadetBlue3(0x8ee5ee);
		const LinearColour CadetBlue4(0x7ac5cd);
		const LinearColour CadetBlue5(0x53868b);
		const LinearColour Chartreuse(0x7fff00);
		const LinearColour Chartreuse2(0x76ee00);
		const LinearColour Chartreuse3(0x66cd00);
		const LinearColour Chartreuse4(0x458b00);
		const LinearColour Chocolate(0xd2691e);
		const LinearColour Chocolate2(0xff7f24);
		const LinearColour Chocolate3(0xee7621);
		const LinearColour Chocolate4(0xcd661d);
		const LinearColour Coral(0xff7f50);
		const LinearColour Coral2(0xff7256);
		const LinearColour Coral3(0xee6a50);
		const LinearColour Coral4(0xcd5b45);
		const LinearColour Coral5(0x8b3e2f);
		const LinearColour CornflowerBlue(0x6495ed);
		const LinearColour Cornsilk(0xfff8dc);
		const LinearColour Cornsilk2(0xeee8cd);
		const LinearColour Cornsilk3(0xcdc8b1);
		const LinearColour Cornsilk4(0x8b8878);
		const LinearColour Cyan(0x00ffff);
		const LinearColour Cyan2(0x00eeee);
		const LinearColour Cyan3(0x00cdcd);
		const LinearColour Cyan4(0x008b8b);
		const LinearColour DarkGoldenrod(0xb8860b);
		const LinearColour DarkGoldenrod2(0xffb90f);
		const LinearColour DarkGoldenrod3(0xeead0e);
		const LinearColour DarkGoldenrod4(0xcd950c);
		const LinearColour DarkGoldenrod5(0x8b6508);
		const LinearColour DarkGreen(0x006400);
		const LinearColour DarkKhaki(0xbdb76b);
		const LinearColour DarkOliveGreen(0x556b2f);
		const LinearColour DarkOliveGreen2(0xcaff70);
		const LinearColour DarkOliveGreen3(0xbcee68);
		const LinearColour DarkOliveGreen4(0xa2cd5a);
		const LinearColour DarkOliveGreen5(0x6e8b3d);
		const LinearColour DarkOrange(0xff8c00);
		const LinearColour DarkOrange2(0xff7f00);
		const LinearColour DarkOrange3(0xee7600);
		const LinearColour DarkOrange4(0xcd6600);
		const LinearColour DarkOrange5(0x8b4500);
		const LinearColour DarkOrchid(0x9932cc);
		const LinearColour DarkOrchid2(0xbf3eff);
		const LinearColour DarkOrchid3(0xb23aee);
		const LinearColour DarkOrchid4(0x9a32cd);
		const LinearColour DarkOrchid5(0x68228b);
		const LinearColour DarkSalmon(0xe9967a);
		const LinearColour DarkSeaGreen(0x8fbc8f);
		const LinearColour DarkSeaGreen2(0xc1ffc1);
		const LinearColour DarkSeaGreen3(0xb4eeb4);
		const LinearColour DarkSeaGreen4(0x9bcd9b);
		const LinearColour DarkSeaGreen5(0x698b69);
		const LinearColour DarkSlateBlue(0x483d8b);
		const LinearColour DarkSlateGray(0x2f4f4f);
		const LinearColour DarkSlateGray2(0x97ffff);
		const LinearColour DarkSlateGray3(0x8deeee);
		const LinearColour DarkSlateGray4(0x79cdcd);
		const LinearColour DarkSlateGray5(0x528b8b);
		const LinearColour DarkTurquoise(0x00ced1);
		const LinearColour DarkViolet(0x9400d3);
		const LinearColour DeepPink(0xff1493);
		const LinearColour DeepPink2(0xee1289);
		const LinearColour DeepPink3(0xcd1076);
		const LinearColour DeepPink4(0x8b0a50);
		const LinearColour DeepSkyBlue(0x00bfff);
		const LinearColour DeepSkyBlue2(0x00b2ee);
		const LinearColour DeepSkyBlue3(0x009acd);
		const LinearColour DeepSkyBlue4(0x00688b);
		const LinearColour DimGray(0x696969);
		const LinearColour DodgerBlue(0x1e90ff);
		const LinearColour DodgerBlue2(0x1c86ee);
		const LinearColour DodgerBlue3(0x1874cd);
		const LinearColour DodgerBlue4(0x104e8b);
		const LinearColour Firebrick(0xb22222);
		const LinearColour Firebrick2(0xff3030);
		const LinearColour Firebrick3(0xee2c2c);
		const LinearColour Firebrick4(0xcd2626);
		const LinearColour Firebrick5(0x8b1a1a);
		const LinearColour Flame(0xE25822);
		const LinearColour FloralWhite(0xfffaf0);
		const LinearColour ForestGreen(0x228b22);
		const LinearColour Gainsboro(0xdcdcdc);
		const LinearColour GhostWhite(0xf8f8ff);
		const LinearColour Gold(0xffd700);
		const LinearColour Gold2(0xeec900);
		const LinearColour Gold3(0xcdad00);
		const LinearColour Gold4(0x8b7500);
		const LinearColour Goldenrod(0xdaa520);
		const LinearColour Goldenrod2(0xffc125);
		const LinearColour Goldenrod3(0xeeb422);
		const LinearColour Goldenrod4(0xcd9b1d);
		const LinearColour Goldenrod5(0x8b6914);
		const LinearColour Gray(0xbebebe);
		const LinearColour Gray01(0x030303);
		const LinearColour Gray02(0x050505);
		const LinearColour Gray03(0x080808);
		const LinearColour Gray04(0x0a0a0a);
		const LinearColour Gray05(0x0d0d0d);
		const LinearColour Gray06(0x0f0f0f);
		const LinearColour Gray07(0x121212);
		const LinearColour Gray08(0x141414);
		const LinearColour Gray09(0x171717);
		const LinearColour Gray10(0x1a1a1a);
		const LinearColour Gray11(0x1c1c1c);
		const LinearColour Gray12(0x1f1f1f);
		const LinearColour Gray13(0x212121);
		const LinearColour Gray14(0x242424);
		const LinearColour Gray15(0x262626);
		const LinearColour Gray16(0x292929);
		const LinearColour Gray17(0x2b2b2b);
		const LinearColour Gray18(0x2e2e2e);
		const LinearColour Gray19(0x303030);
		const LinearColour Gray20(0x333333);
		const LinearColour Gray21(0x363636);
		const LinearColour Gray22(0x383838);
		const LinearColour Gray23(0x3b3b3b);
		const LinearColour Gray24(0x3d3d3d);
		const LinearColour Gray25(0x404040);
		const LinearColour Gray26(0x424242);
		const LinearColour Gray27(0x454545);
		const LinearColour Gray28(0x474747);
		const LinearColour Gray29(0x4a4a4a);
		const LinearColour Gray30(0x4d4d4d);
		const LinearColour Gray31(0x4f4f4f);
		const LinearColour Gray32(0x525252);
		const LinearColour Gray33(0x545454);
		const LinearColour Gray34(0x575757);
		const LinearColour Gray35(0x595959);
		const LinearColour Gray36(0x5c5c5c);
		const LinearColour Gray37(0x5e5e5e);
		const LinearColour Gray38(0x616161);
		const LinearColour Gray39(0x636363);
		const LinearColour Gray40(0x666666);
		const LinearColour Gray41(0x696969);
		const LinearColour Gray42(0x6b6b6b);
		const LinearColour Gray43(0x6e6e6e);
		const LinearColour Gray44(0x707070);
		const LinearColour Gray45(0x737373);
		const LinearColour Gray46(0x757575);
		const LinearColour Gray47(0x787878);
		const LinearColour Gray48(0x7a7a7a);
		const LinearColour Gray49(0x7d7d7d);
		const LinearColour Gray50(0x7f7f7f);
		const LinearColour Gray51(0x828282);
		const LinearColour Gray52(0x858585);
		const LinearColour Gray53(0x878787);
		const LinearColour Gray54(0x8a8a8a);
		const LinearColour Gray55(0x8c8c8c);
		const LinearColour Gray56(0x8f8f8f);
		const LinearColour Gray57(0x919191);
		const LinearColour Gray58(0x949494);
		const LinearColour Gray59(0x969696);
		const LinearColour Gray60(0x999999);
		const LinearColour Gray61(0x9c9c9c);
		const LinearColour Gray62(0x9e9e9e);
		const LinearColour Gray63(0xa1a1a1);
		const LinearColour Gray64(0xa3a3a3);
		const LinearColour Gray65(0xa6a6a6);
		const LinearColour Gray66(0xa8a8a8);
		const LinearColour Gray67(0xababab);
		const LinearColour Gray68(0xadadad);
		const LinearColour Gray69(0xb0b0b0);
		const LinearColour Gray70(0xb3b3b3);
		const LinearColour Gray71(0xb5b5b5);
		const LinearColour Gray72(0xb8b8b8);
		const LinearColour Gray73(0xbababa);
		const LinearColour Gray74(0xbdbdbd);
		const LinearColour Gray75(0xbfbfbf);
		const LinearColour Gray76(0xc2c2c2);
		const LinearColour Gray77(0xc4c4c4);
		const LinearColour Gray78(0xc7c7c7);
		const LinearColour Gray79(0xc9c9c9);
		const LinearColour Gray80(0xcccccc);
		const LinearColour Gray81(0xcfcfcf);
		const LinearColour Gray82(0xd1d1d1);
		const LinearColour Gray83(0xd4d4d4);
		const LinearColour Gray84(0xd6d6d6);
		const LinearColour Gray85(0xd9d9d9);
		const LinearColour Gray86(0xdbdbdb);
		const LinearColour Gray87(0xdedede);
		const LinearColour Gray88(0xe0e0e0);
		const LinearColour Gray89(0xe3e3e3);
		const LinearColour Gray90(0xe5e5e5);
		const LinearColour Gray91(0xe8e8e8);
		const LinearColour Gray92(0xebebeb);
		const LinearColour Gray93(0xededed);
		const LinearColour Gray94(0xf0f0f0);
		const LinearColour Gray95(0xf2f2f2);
		const LinearColour Gray97(0xf7f7f7);
		const LinearColour Gray98(0xfafafa);
		const LinearColour Gray99(0xfcfcfc);
		const LinearColour Green(0x00ff00);
		const LinearColour Green2(0x00ee00);
		const LinearColour Green3(0x00cd00);
		const LinearColour Green4(0x008b00);
		const LinearColour GreenYellow(0xadff2f);
		const LinearColour Honeydew(0xf0fff0);
		const LinearColour Honeydew2(0xe0eee0);
		const LinearColour Honeydew3(0xc1cdc1);
		const LinearColour Honeydew4(0x838b83);
		const LinearColour HotPink(0xff69b4);
		const LinearColour HotPink2(0xff6eb4);
		const LinearColour HotPink3(0xee6aa7);
		const LinearColour HotPink4(0xcd6090);
		const LinearColour HotPink5(0x8b3a62);
		const LinearColour IndianRed(0xcd5c5c);
		const LinearColour IndianRed2(0xff6a6a);
		const LinearColour IndianRed3(0xee6363);
		const LinearColour IndianRed4(0xcd5555);
		const LinearColour IndianRed5(0x8b3a3a);
		const LinearColour Ivory(0xfffff0);
		const LinearColour Ivory2(0xeeeee0);
		const LinearColour Ivory3(0xcdcdc1);
		const LinearColour Ivory4(0x8b8b83);
		const LinearColour Khaki(0xf0e68c);
		const LinearColour Khaki2(0xfff68f);
		const LinearColour Khaki3(0xeee685);
		const LinearColour Khaki4(0xcdc673);
		const LinearColour Khaki5(0x8b864e);
		const LinearColour Lavender(0xe6e6fa);
		const LinearColour LavenderBlush(0xfff0f5);
		const LinearColour LavenderBlush2(0xeee0e5);
		const LinearColour LavenderBlush3(0xcdc1c5);
		const LinearColour LavenderBlush4(0x8b8386);
		const LinearColour LawnGreen(0x7cfc00);
		const LinearColour LemonChiffon(0xfffacd);
		const LinearColour LemonChiffon2(0xeee9bf);
		const LinearColour LemonChiffon3(0xcdc9a5);
		const LinearColour LemonChiffon4(0x8b8970);
		const LinearColour Light(0xeedd82);
		const LinearColour LightBlue(0xadd8e6);
		const LinearColour LightBlue2(0xbfefff);
		const LinearColour LightBlue3(0xb2dfee);
		const LinearColour LightBlue4(0x9ac0cd);
		const LinearColour LightBlue5(0x68838b);
		const LinearColour LightCoral(0xf08080);
		const LinearColour LightCyan(0xe0ffff);
		const LinearColour LightCyan2(0xd1eeee);
		const LinearColour LightCyan3(0xb4cdcd);
		const LinearColour LightCyan4(0x7a8b8b);
		const LinearColour LightGoldenrod(0xffec8b);
		const LinearColour LightGoldenrod2(0xeedc82);
		const LinearColour LightGoldenrod3(0xcdbe70);
		const LinearColour LightGoldenrod4(0x8b814c);
		const LinearColour LightGoldenrodYellow(0xfafad2);
		const LinearColour LightGray(0xd3d3d3);
		const LinearColour LightPink(0xffb6c1);
		const LinearColour LightPink2(0xffaeb9);
		const LinearColour LightPink3(0xeea2ad);
		const LinearColour LightPink4(0xcd8c95);
		const LinearColour LightPink5(0x8b5f65);
		const LinearColour LightSalmon(0xffa07a);
		const LinearColour LightSalmon2(0xee9572);
		const LinearColour LightSalmon3(0xcd8162);
		const LinearColour LightSalmon4(0x8b5742);
		const LinearColour LightSeaGreen(0x20b2aa);
		const LinearColour LightSkyBlue(0x87cefa);
		const LinearColour LightSkyBlue2(0xb0e2ff);
		const LinearColour LightSkyBlue3(0xa4d3ee);
		const LinearColour LightSkyBlue4(0x8db6cd);
		const LinearColour LightSkyBlue5(0x607b8b);
		const LinearColour LightSlateBlue(0x8470ff);
		const LinearColour LightSlateGray(0x778899);
		const LinearColour LightSteelBlue(0xb0c4de);
		const LinearColour LightSteelBlue2(0xcae1ff);
		const LinearColour LightSteelBlue3(0xbcd2ee);
		const LinearColour LightSteelBlue4(0xa2b5cd);
		const LinearColour LightSteelBlue5(0x6e7b8b);
		const LinearColour LightYellow(0xffffe0);
		const LinearColour LightYellow2(0xeeeed1);
		const LinearColour LightYellow3(0xcdcdb4);
		const LinearColour LightYellow4(0x8b8b7a);
		const LinearColour LimeGreen(0x32cd32);
		const LinearColour Linen(0xfaf0e6);
		const LinearColour Magenta(0xff00ff);
		const LinearColour Magenta2(0xee00ee);
		const LinearColour Magenta3(0xcd00cd);
		const LinearColour Magenta4(0x8b008b);
		const LinearColour Maroon(0xb03060);
		const LinearColour Maroon2(0xff34b3);
		const LinearColour Maroon3(0xee30a7);
		const LinearColour Maroon4(0xcd2990);
		const LinearColour Maroon5(0x8b1c62);
		const LinearColour Medium(0x66cdaa);
		const LinearColour MediumAquamarine(0x66cdaa);
		const LinearColour MediumBlue(0x0000cd);
		const LinearColour MediumOrchid(0xba55d3);
		const LinearColour MediumOrchid2(0xe066ff);
		const LinearColour MediumOrchid3(0xd15fee);
		const LinearColour MediumOrchid4(0xb452cd);
		const LinearColour MediumOrchid5(0x7a378b);
		const LinearColour MediumPurple(0x9370db);
		const LinearColour MediumPurple2(0xab82ff);
		const LinearColour MediumPurple3(0x9f79ee);
		const LinearColour MediumPurple4(0x8968cd);
		const LinearColour MediumPurple5(0x5d478b);
		const LinearColour MediumSeaGreen(0x3cb371);
		const LinearColour MediumSlateBlue(0x7b68ee);
		const LinearColour MediumSpringGreen(0x00fa9a);
		const LinearColour MediumTurquoise(0x48d1cc);
		const LinearColour MediumVioletRed(0xc71585);
		const LinearColour MidnightBlue(0x191970);
		const LinearColour MintCream(0xf5fffa);
		const LinearColour MistyRose(0xffe4e1);
		const LinearColour MistyRose2(0xeed5d2);
		const LinearColour MistyRose3(0xcdb7b5);
		const LinearColour MistyRose4(0x8b7d7b);
		const LinearColour Moccasin(0xffe4b5);
		const LinearColour NavajoWhite(0xffdead);
		const LinearColour NavajoWhite2(0xeecfa1);
		const LinearColour NavajoWhite3(0xcdb38b);
		const LinearColour NavajoWhite4(0x8b795e);
		const LinearColour NavyBlue(0x000080);
		const LinearColour OldLace(0xfdf5e6);
		const LinearColour OliveDrab(0x6b8e23);
		const LinearColour OliveDrab2(0xc0ff3e);
		const LinearColour OliveDrab3(0xb3ee3a);
		const LinearColour OliveDrab5(0x698b22);
		const LinearColour Orange(0xffa500);
		const LinearColour Orange2(0xee9a00);
		const LinearColour Orange3(0xcd8500);
		const LinearColour Orange4(0x8b5a00);
		const LinearColour OrangeRed(0xff4500);
		const LinearColour OrangeRed2(0xee4000);
		const LinearColour OrangeRed3(0xcd3700);
		const LinearColour OrangeRed4(0x8b2500);
		const LinearColour Orchid(0xda70d6);
		const LinearColour Orchid2(0xff83fa);
		const LinearColour Orchid3(0xee7ae9);
		const LinearColour Orchid4(0xcd69c9);
		const LinearColour Orchid5(0x8b4789);
		const LinearColour Pale(0xdb7093);
		const LinearColour PaleGoldenrod(0xeee8aa);
		const LinearColour PaleGreen(0x98fb98);
		const LinearColour PaleGreen2(0x9aff9a);
		const LinearColour PaleGreen3(0x90ee90);
		const LinearColour PaleGreen4(0x7ccd7c);
		const LinearColour PaleGreen5(0x548b54);
		const LinearColour PaleTurquoise(0xafeeee);
		const LinearColour PaleTurquoise2(0xbbffff);
		const LinearColour PaleTurquoise3(0xaeeeee);
		const LinearColour PaleTurquoise4(0x96cdcd);
		const LinearColour PaleTurquoise5(0x668b8b);
		const LinearColour PaleVioletRed(0xdb7093);
		const LinearColour PaleVioletRed2(0xff82ab);
		const LinearColour PaleVioletRed3(0xee799f);
		const LinearColour PaleVioletRed4(0xcd6889);
		const LinearColour PaleVioletRed5(0x8b475d);
		const LinearColour PapayaWhip(0xffefd5);
		const LinearColour PeachPuff(0xffdab9);
		const LinearColour PeachPuff2(0xeecbad);
		const LinearColour PeachPuff3(0xcdaf95);
		const LinearColour PeachPuff4(0x8b7765);
		const LinearColour Pink(0xffc0cb);
		const LinearColour Pink2(0xffb5c5);
		const LinearColour Pink3(0xeea9b8);
		const LinearColour Pink4(0xcd919e);
		const LinearColour Pink5(0x8b636c);
		const LinearColour Plum(0xdda0dd);
		const LinearColour Plum2(0xffbbff);
		const LinearColour Plum3(0xeeaeee);
		const LinearColour Plum4(0xcd96cd);
		const LinearColour Plum5(0x8b668b);
		const LinearColour PowderBlue(0xb0e0e6);
		const LinearColour RebeccaPurple(0x663399);
		const LinearColour Purple(0xa020f0);
		const LinearColour Purple2(0x9b30ff);
		const LinearColour Purple3(0x912cee);
		const LinearColour Purple4(0x7d26cd);
		const LinearColour Purple5(0x551a8b);
		const LinearColour Red(0xff0000);
		const LinearColour Red2(0xee0000);
		const LinearColour Red3(0xcd0000);
		const LinearColour Red4(0x8b0000);
		const LinearColour RosyBrown(0xbc8f8f);
		const LinearColour RosyBrown2(0xffc1c1);
		const LinearColour RosyBrown3(0xeeb4b4);
		const LinearColour RosyBrown4(0xcd9b9b);
		const LinearColour RosyBrown5(0x8b6969);
		const LinearColour RoyalBlue(0x4169e1);
		const LinearColour RoyalBlue2(0x4876ff);
		const LinearColour RoyalBlue3(0x436eee);
		const LinearColour RoyalBlue4(0x3a5fcd);
		const LinearColour RoyalBlue5(0x27408b);
		const LinearColour SaddleBrown(0x8b4513);
		const LinearColour Salmon(0xfa8072);
		const LinearColour Salmon2(0xff8c69);
		const LinearColour Salmon3(0xee8262);
		const LinearColour Salmon4(0xcd7054);
		const LinearColour Salmon5(0x8b4c39);
		const LinearColour SandyBrown(0xf4a460);
		const LinearColour SeaGreen(0x54ff9f);
		const LinearColour SeaGreen2(0x4eee94);
		const LinearColour SeaGreen3(0x43cd80);
		const LinearColour SeaGreen4(0x2e8b57);
		const LinearColour Seashell(0xfff5ee);
		const LinearColour Seashell2(0xeee5de);
		const LinearColour Seashell3(0xcdc5bf);
		const LinearColour Seashell4(0x8b8682);
		const LinearColour Sienna(0xa0522d);
		const LinearColour Sienna2(0xff8247);
		const LinearColour Sienna3(0xee7942);
		const LinearColour Sienna4(0xcd6839);
		const LinearColour Sienna5(0x8b4726);
		const LinearColour SkyBlue(0x87ceeb);
		const LinearColour SkyBlue2(0x87ceff);
		const LinearColour SkyBlue3(0x7ec0ee);
		const LinearColour SkyBlue4(0x6ca6cd);
		const LinearColour SkyBlue5(0x4a708b);
		const LinearColour SlateBlue(0x6a5acd);
		const LinearColour SlateBlue2(0x836fff);
		const LinearColour SlateBlue3(0x7a67ee);
		const LinearColour SlateBlue4(0x6959cd);
		const LinearColour SlateBlue5(0x473c8b);
		const LinearColour SlateGray(0x708090);
		const LinearColour SlateGray2(0xc6e2ff);
		const LinearColour SlateGray3(0xb9d3ee);
		const LinearColour SlateGray4(0x9fb6cd);
		const LinearColour SlateGray5(0x6c7b8b);
		const LinearColour Snow(0xfffafa);
		const LinearColour Snow2(0xeee9e9);
		const LinearColour Snow3(0xcdc9c9);
		const LinearColour Snow4(0x8b8989);
		const LinearColour SpringGreen(0x00ff7f);
		const LinearColour SpringGreen2(0x00ee76);
		const LinearColour SpringGreen3(0x00cd66);
		const LinearColour SpringGreen4(0x008b45);
		const LinearColour SteelBlue(0x4682b4);
		const LinearColour SteelBlue2(0x63b8ff);
		const LinearColour SteelBlue3(0x5cacee);
		const LinearColour SteelBlue4(0x4f94cd);
		const LinearColour SteelBlue5(0x36648b);
		const LinearColour Tan(0xd2b48c);
		const LinearColour Tan2(0xffa54f);
		const LinearColour Tan3(0xee9a49);
		const LinearColour Tan4(0xcd853f);
		const LinearColour Tan5(0x8b5a2b);
		const LinearColour Thistle(0xd8bfd8);
		const LinearColour Thistle2(0xffe1ff);
		const LinearColour Thistle3(0xeed2ee);
		const LinearColour Thistle4(0xcdb5cd);
		const LinearColour Thistle5(0x8b7b8b);
		const LinearColour Tomato(0xff6347);
		const LinearColour Tomato2(0xee5c42);
		const LinearColour Tomato3(0xcd4f39);
		const LinearColour Tomato4(0x8b3626);
		const LinearColour Turquoise(0x40e0d0);
		const LinearColour Turquoise2(0x00f5ff);
		const LinearColour Turquoise3(0x00e5ee);
		const LinearColour Turquoise4(0x00c5cd);
		const LinearColour Turquoise5(0x00868b);
		const LinearColour Violet(0xee82ee);
		const LinearColour VioletRed(0xd02090);
		const LinearColour VioletRed2(0xff3e96);
		const LinearColour VioletRed3(0xee3a8c);
		const LinearColour VioletRed4(0xcd3278);
		const LinearColour VioletRed5(0x8b2252);
		const LinearColour Wheat(0xf5deb3);
		const LinearColour Wheat2(0xffe7ba);
		const LinearColour Wheat3(0xeed8ae);
		const LinearColour Wheat4(0xcdba96);
		const LinearColour Wheat5(0x8b7e66);
		const LinearColour White(0xffffff);
		const LinearColour WhiteSmoke(0xf5f5f5);
		const LinearColour Yellow(0xffff00);
		const LinearColour Yellow2(0xeeee00);
		const LinearColour Yellow3(0xcdcd00);
		const LinearColour Yellow4(0x8b8b00);
		const LinearColour YellowGreen(0x9acd32);
	}
} // namespace Visualization

#endif // #ifdef IncludedMathLinearColourH