#pragma once

#include "base.hpp"
#include "amath.hpp"
#include "vector.hpp"

namespace nl {
	constexpr float linearInterpolation(float a, float b, float pos, float range) {
		return a + (b - a) * (pos / range);
	};
	constexpr float linearInterpolation(float a, float b, float pos) {
		return linearInterpolation(a, b, pos, 1.0f);
	};

	constexpr float bilinearInterpolation(float aa, float ba, float ab, float bb, const vec2<float>& pos, const vec2<float>& range) {
		float ia = linearInterpolation(aa, ba, pos[0], range[0]);
		float ib = linearInterpolation(ab, bb, pos[0], range[0]);

		return linearInterpolation(ia, ib, pos[1], range[1]);
	};
	constexpr float bilinearInterpolation(float aa, float ba, float ab, float bb, const vec2<float>& pos, float range) {
		return bilinearInterpolation(aa, ba, ab, bb, pos, vec2<float>(range));
	};
	constexpr float bilinearInterpolation(float aa, float ba, float ab, float bb, const vec2<float>& pos) {
		return bilinearInterpolation(aa, ba, ab, bb, pos, vec2<float>(1.0f));
	};

	constexpr float trilinearInterpolation(float aaa, float baa, float aba, float bba, float aab, float bab, float abb, float bbb, const vec3<float>& pos, const vec3<float>& range) {
		float iia = bilinearInterpolation(aaa, baa, aba, bba, vec2<float>({ pos[0], pos[1] }), vec2<float>({ range[0], range[1] }));
		float iib = bilinearInterpolation(aab, bab, abb, bbb, vec2<float>({ pos[0], pos[1] }), vec2<float>({ range[0], range[1] }));

		return linearInterpolation(iia, iib, pos[2], range[2]);
	};
	constexpr float trilinearInterpolation(float aaa, float baa, float aba, float bba, float aab, float bab, float abb, float bbb, const vec3<float>& pos, float range) {
		return trilinearInterpolation(aaa, baa, aba, bba, aab, bab, abb, bbb, pos, vec2<float>(range));
	};
	constexpr float trilinearInterpolation(float aaa, float baa, float aba, float bba, float aab, float bab, float abb, float bbb, const vec3<float>& pos) {
		return trilinearInterpolation(aaa, baa, aba, bba, aab, bab, abb, bbb, pos, 1.0f);
	};

	constexpr float cubicInterpolation(float a, float b, float c, float d, float pos, float range) {
		pos /= range;
		
		float p0 = b * (2.0f * pos * pos * pos - 3.0f * pos * pos + 1.0f);
		float m0 = (c - a) / 2.0f * (pos * pos * pos - 2.0f * pos * pos + pos);
		float p1 = c * (-2.0f * pos * pos * pos + 3 * pos * pos);
		float m1 = (d - b) / 2.0f * (pos * pos * pos - pos * pos);

		return p0 + m0 + p1 + m1;
	};
	constexpr float cubicInterpolation(float a, float b, float c, float d, float pos) {
		return cubicInterpolation(a, b, c, d, pos, 1.0f);
	};

	constexpr float bicubicInterpolation(
		float aa, float ba, float ca, float da,
		float ab, float bb, float cb, float db,
		float ac, float bc, float cc, float dc,
		float ad, float bd, float cd, float dd,
		const vec2<float>& pos, const vec2<float>& range) {
		float ia = cubicInterpolation(aa, ba, ca, da, pos[0], range[0]);
		float ib = cubicInterpolation(ab, bb, cb, db, pos[0], range[0]);
		float ic = cubicInterpolation(ac, bc, cc, dc, pos[0], range[0]);
		float id = cubicInterpolation(ad, bd, cd, dd, pos[0], range[0]);
		
		return cubicInterpolation(ia, ib, ic, id, pos[1], range[1]);
	};
	constexpr float bicubicInterpolation(
		float aa, float ba, float ca, float da,
		float ab, float bb, float cb, float db,
		float ac, float bc, float cc, float dc,
		float ad, float bd, float cd, float dd,
		const vec2<float>& pos, float range) {
		return bicubicInterpolation(aa, ba, ca, da, ab, bb, cb, db, ac, bc, cc, dc, ad, bd, cd, dd, pos, vec2<float>(range));
	};
	constexpr float bicubicInterpolation(
		float aa, float ba, float ca, float da,
		float ab, float bb, float cb, float db,
		float ac, float bc, float cc, float dc,
		float ad, float bd, float cd, float dd,
		const vec2<float>& pos) {
		return bicubicInterpolation(aa, ba, ca, da, ab, bb, cb, db, ac, bc, cc, dc, ad, bd, cd, dd, pos, 1.0f);
	};
};\