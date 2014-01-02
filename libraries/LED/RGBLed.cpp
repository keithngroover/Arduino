#include "RGBLed.h"
#include <Arduino.h>
#include <math.h>

Color hsvToRGB(float hue, float saturation, float value)
{
	float hh, p, q, t, ff;
	long i;
	Color out;
	hue = min(max(hue, 0.f), 360.f);
	saturation = min(max(saturation, 0.f), 1.f);
	value = min(max(value, 0.f), 1.f);
	if (saturation <= 0.f)
	{
		out.r = value * 255;
		out.g = value * 255;
		out.b = value * 255;
	}
	else
	{
		hh = hue;
		if (hh >= 360.f)
		{
			hh -= 360.f;
		}
		hh /= 60.f;
		i = (long)hh;
		ff = hh - i;
		p = value * (1.f - saturation);
		q = value * (1.f - (saturation * ff));
		t = value * (1.f - (saturation * (1.f - ff)));
		
		switch (i)
		{
			case 0:
				out.r = value * 255;
				out.g = t * 255;
				out.b = p * 255;
				break;
			case 1:
				out.r = q * 255;
				out.g = value * 255;
				out.b = p * 255;
				break;
			case 2:
				out.r = p * 255;
				out.g = value * 255;
				out.b = t * 255;
				break;
			case 3:
				out.r = p * 255;
				out.g = q * 255;
				out.b = value * 255;
				break;
			case 4:
				out.r = t * 255;
				out.g = p * 255;
				out.b = value * 255;
				break;
			case 5:
			default:
				out.r = value * 255;
				out.g = p * 255;
				out.b = q * 255;
				break;
		};
	}
	return out;
}

RGBLed::RGBLed() : redPin(-1), greenPin(-1), bluePin(-1)
{

}

RGBLed::RGBLed(int iRedPin, int iGreenPin, int iBluePin) : redPin(iRedPin), greenPin(iGreenPin), bluePin(iBluePin)
{
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
}

void RGBLed::setRGB(int red, int green, int blue)
{
	if (-1 == redPin || -1 == greenPin || -1 == bluePin)
	{
		return;
	}
	analogWrite(redPin, red);
	analogWrite(greenPin, green);
	analogWrite(bluePin, blue);
}

void RGBLed::setRGB(float red, float green, float blue)
{
	setRGB(int(red * 255), int(green * 255), int(blue * 255));
}

void RGBLed::setHSV(float hue, float saturation, float value)
{
	Color result = hsvToRGB(hue, saturation, value);
	setRGB(result.r, result.g, result.b);
}