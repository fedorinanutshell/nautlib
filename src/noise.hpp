#pragma once

#include <unordered_map>
#include <numbers>
#include <algorithm>

#include "amath.hpp"
#include "base.hpp"
#include "vector.hpp"
#include "random.hpp"
#include "interpolation.hpp"

namespace nl {
	class baseValNoise2d {
	public:
		std::unordered_map<vec2<s32>, float> map;
		u32 seed = 1;

		baseValNoise2d() = default;
		baseValNoise2d(u32 srcSeed) {
			seed = nl::random_u32(srcSeed);
		};

		float getLatticePoint(const vec2<s32>& coord) {
			if (map.contains(coord)) {
				return map[coord];
			}
			else {
				float val = random_float(random_u32((coord[0] ^ (~coord[1] << 16 ^ coord[1] >> 16)) * seed) ^ seed);
				map[coord] = val;
				return val;
			};
		};
		float getLatticePoint(s32 x, s32 y) {
			return getLatticePoint(vec2<s32>({ x, y }));
		};

		float getPoint(const vec2<float>& coord) {
			vec2<s32> icoord = coord;
			vec2<float> fcoord = coord - vec2<float>(icoord);
			float laa = getLatticePoint(icoord[0], icoord[1]);
			float lab = getLatticePoint(icoord[0], icoord[1] + 1);
			float lba = getLatticePoint(icoord[0] + 1, icoord[1]);
			float lbb = getLatticePoint(icoord[0] + 1, icoord[1] + 1);

			float aa = getLatticePoint(icoord[0] - 1, icoord[1] - 1);
			float ba = getLatticePoint(icoord[0], icoord[1] - 1);
			float ca = getLatticePoint(icoord[0] + 1, icoord[1] - 1);
			float da = getLatticePoint(icoord[0] + 2, icoord[1] - 1);

			float ab = getLatticePoint(icoord[0] - 1, icoord[1]);
			float bb = getLatticePoint(icoord[0], icoord[1]);
			float cb = getLatticePoint(icoord[0] + 1, icoord[1]);
			float db = getLatticePoint(icoord[0] + 2, icoord[1]);

			float ac = getLatticePoint(icoord[0] - 1, icoord[1] + 1);
			float bc = getLatticePoint(icoord[0], icoord[1] + 1);
			float cc = getLatticePoint(icoord[0] + 1, icoord[1] + 1);
			float dc = getLatticePoint(icoord[0] + 2, icoord[1] + 1);

			float ad = getLatticePoint(icoord[0] - 1, icoord[1] + 2);
			float bd = getLatticePoint(icoord[0], icoord[1] + 2);
			float cd = getLatticePoint(icoord[0] + 1, icoord[1] + 2);
			float dd = getLatticePoint(icoord[0] + 2, icoord[1] + 2);

			float res = bicubicInterpolation(aa, ba, ca, da,
				ab, bb, cb, db,
				ac, bc, cc, dc,
				ad, bd, cd, dd, fcoord, 1.0f);
			return res;
		};
	};

	class basePerlin2d {
	public:
		std::unordered_map<vec2<s32>, float> map;
		u32 seed = 1;

		basePerlin2d() = default;
		basePerlin2d(u32 srcSeed) {
			seed = nl::random_u32(srcSeed);
		};

		float getLatticeAngle(const vec2<s32>& coord) {
			if (map.contains(coord)) {
				return map[coord];
			}
			else {
				float val = random_float(random_u32((coord[0] ^ (~coord[1] << 16 ^ coord[1] >> 16)) * seed) ^ seed) * std::numbers::pi_v<float> * 2.0f;
				map[coord] = val;
				return val;
			};
		};
		float getLatticeAngle(s32 x, s32 y) {
			return getLatticeAngle(vec2<s32>({ x, y }));
		};

		vec2<float> getLatticeGradient(const vec2<s32>& coord) {
			float angle = getLatticeAngle(coord);
			return vec2<float>({ std::cosf(angle), std::sinf(angle) }) / 1.0f;
		};
		vec2<float> getLatticeGradient(s32 x, s32 y) {
			return getLatticeGradient(vec2<s32>({ x, y }));
		};

		float getRawPoint(const vec2<s32>& icoord, const vec2<float>& fcoord) {
			vec2<float> delta = (fcoord - vec2<float>(icoord)) * 2.0f;
			vec2<float> grad = getLatticeGradient(icoord);
			return grad & delta;
		};
		float getRawPoint(s32 ix, s32 iy, float fx, float fy) {
			return getRawPoint(vec2<s32>({ ix, iy }), vec2<float>({ fx, fy }));
		};

		float getPoint(const vec2<float>& coord) {
			vec2<s32> icoord({ s32(std::floor(coord[0])), s32(std::floor(coord[1])) });
			vec2<float> fcoord = coord - vec2<float>(icoord);

			float aa = getRawPoint(icoord[0] - 1, icoord[1] - 1, coord[0], coord[1]);
			float ba = getRawPoint(icoord[0], icoord[1] - 1, coord[0], coord[1]);
			float ca = getRawPoint(icoord[0] + 1, icoord[1] - 1, coord[0], coord[1]);
			float da = getRawPoint(icoord[0] + 2, icoord[1] - 1, coord[0], coord[1]);

			float ab = getRawPoint(icoord[0] - 1, icoord[1], coord[0], coord[1]);
			float bb = getRawPoint(icoord[0], icoord[1], coord[0], coord[1]);
			float cb = getRawPoint(icoord[0] + 1, icoord[1], coord[0], coord[1]);
			float db = getRawPoint(icoord[0] + 2, icoord[1], coord[0], coord[1]);

			float ac = getRawPoint(icoord[0] - 1, icoord[1] + 1, coord[0], coord[1]);
			float bc = getRawPoint(icoord[0], icoord[1] + 1, coord[0], coord[1]);
			float cc = getRawPoint(icoord[0] + 1, icoord[1] + 1, coord[0], coord[1]);
			float dc = getRawPoint(icoord[0] + 2, icoord[1] + 1, coord[0], coord[1]);

			float ad = getRawPoint(icoord[0] - 1, icoord[1] + 2, coord[0], coord[1]);
			float bd = getRawPoint(icoord[0], icoord[1] + 2, coord[0], coord[1]);
			float cd = getRawPoint(icoord[0] + 1, icoord[1] + 2, coord[0], coord[1]);
			float dd = getRawPoint(icoord[0] + 2, icoord[1] + 2, coord[0], coord[1]);

			float res = bicubicInterpolation(aa, ba, ca, da,
				ab, bb, cb, db,
				ac, bc, cc, dc,
				ad, bd, cd, dd, fcoord);
			return res;
		};
	};

	struct noiseParameters {
		float lacunarity = 0.5f;
		float persistency = 0.5f;
		bool sign = true;

		float scale = 1.0f;
		u8 octaves = 8;
		u32 seed = 1;
		bool abs = false;
	};

	class perlin2d {
	public:
		std::unordered_map<u8, basePerlin2d> map;
		noiseParameters np;

		perlin2d(const noiseParameters& srcNP) {
			np = srcNP;
			u32 seed = 1;
			for (u8 o = 0; o < np.octaves; o++) {
				seed *= np.seed + 1;
				map[o] = basePerlin2d(seed);
			};
		};

		float getPoint(vec2<float> coord) {
			coord /= np.scale;
			float lacunarity = 1.0f;
			float persistency = 1.0f;

			float res = 0.0f;
			for (u8 o = 0; o < np.octaves; o++) {
				lacunarity *= np.lacunarity;
				persistency *= np.persistency;

				float val = map[o].getPoint(coord / lacunarity);
				val = np.sign ? val : (val / 2.0f + 0.5f);
				val *= persistency;

				res += val;
			};

			res = np.abs ? std::abs(res) : res;
			return res;
		};
	};
};