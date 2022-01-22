#pragma once

#include "base.hpp"
#include "amath.hpp"

namespace nl {
	constexpr u8 reverse(u8 val) {
		u8 x = (val & 0x55) << 1 | (val & 0xaa) >> 1;
		x = (x & 0x33) << 2 | (x & 0xcc) >> 2;
		x = (x & 0x0f) << 4 | (x & 0xf0) >> 4;
		return x;
	};

	constexpr u16 reverse(u16 val) {
		u16 x = (val & 0x5555) << 1 | (val & 0xaaaa) >> 1;
		x = (x & 0x3333) << 2 | (x & 0xcccc) >> 2;
		x = (x & 0x0f0f) << 4 | (x & 0xf0f0) >> 4;
		x = (x & 0x00ff) << 8 | (x & 0xff00) >> 8;
		return x;
	};

	constexpr u32 reverse(u32 val) {
		u32 x = (val & 0x55555555) << 1 | (val & 0xaaaaaaaa) >> 1;
		x = (x & 0x33333333) << 2 | (x & 0xcccccccc) >> 2;
		x = (x & 0x0f0f0f0f) << 4 | (x & 0xf0f0f0f0) >> 4;
		x = (x & 0x00ff00ff) << 8 | (x & 0xff00ff00) >> 8;
		x = (x & 0x0000ffff) << 16 | (x & 0xffff0000) >> 16;
		return x;
	};

	constexpr u64 reverse(u64 val) {
		u64 x = (val & 0x5555555555555555) << 1 | (val & 0xaaaaaaaaaaaaaaaa) >> 1;
		x = (x & 0x3333333333333333) << 2 | (x & 0xcccccccccccccccc) >> 2;
		x = (x & 0x0f0f0f0f0f0f0f0f) << 4 | (x & 0xf0f0f0f0f0f0f0f0) >> 4;
		x = (x & 0x00ff00ff00ff00ff) << 8 | (x & 0xff00ff00ff00ff00) >> 8;
		x = (x & 0x0000ffff0000ffff) << 16 | (x & 0xffff0000ffff0000) >> 16;
		x = (x & 0x00000000ffffffff) << 32 | (x & 0xffffffff00000000) >> 32;
		return x;
	};

	constexpr u8 bitshuffle(u8 val) {
		u8 x = (val << 4) | (val >> 4);
		x = (x & 0x0c) << 2 | (x >> 2) & 0x0c | x & 0xc3;
		x = (x & 0x22) << 1 | (x >> 1) & 0x22 | x & 0x99;
		return x;
	};

	constexpr u16 bitshuffle(u16 val) {
		u16 x = (val << 8) | (val >> 8);
		x = (x & 0x00f0) << 4 | (x >> 4) & 0x00f0 | x & 0xf00f;
		x = (x & 0x0c0c) << 2 | (x >> 2) & 0x0c0c | x & 0xc3c3;
		x = (x & 0x2222) << 1 | (x >> 1) & 0x2222 | x & 0x9999;
		return x;
	};

	constexpr u32 bitshuffle(u32 val) {
		u32 x = (val << 16) | (val >> 16);
		x = (x & 0x0000ff00) << 8 | (x >> 8) & 0x0000ff00 | x & 0xff0000ff;
		x = (x & 0x00f000f0) << 4 | (x >> 4) & 0x00f000f0 | x & 0xf00ff00f;
		x = (x & 0x0c0c0c0c) << 2 | (x >> 2) & 0x0c0c0c0c | x & 0xc3c3c3c3;
		x = (x & 0x22222222) << 1 | (x >> 1) & 0x22222222 | x & 0x99999999;
		return x;
	};

	constexpr u64 bitshuffle(u64 val) {
		u64 x = (val << 32) | (val >> 32);
		x = (x & 0x00000000ffff0000) << 16 | (x >> 16) & 0x00000000ffff0000 | x & 0xffff00000000ffff;
		x = (x & 0x0000ff000000ff00) << 8 | (x >> 8) & 0x0000ff000000ff00 | x & 0xff0000ffff0000ff;
		x = (x & 0x00f000f000f000f0) << 4 | (x >> 4) & 0x00f000f000f000f0 | x & 0xf00ff00ff00ff00f;
		x = (x & 0x0c0c0c0c0c0c0c0c) << 2 | (x >> 2) & 0x0c0c0c0c0c0c0c0c | x & 0xc3c3c3c3c3c3c3c3;
		x = (x & 0x2222222222222222) << 1 | (x >> 1) & 0x2222222222222222 | x & 0x9999999999999999;
		return x;
	};

	constexpr u8 randombit_u8(u8 seed) {
		return ~nl::bitshuffle(nl::reverse(seed));
	};

	constexpr u16 randombit_u16(u16 seed) {
		return ~nl::bitshuffle(nl::reverse(seed));
	};

	constexpr u32 randombit_u32(u32 seed) {
		return ~nl::bitshuffle(nl::reverse(seed));
	};

	constexpr u64 randombit_u64(u64 seed) {
		return ~nl::bitshuffle(nl::reverse(seed));
	};

	constexpr u8 randomlcg_u8(u8 seed) {
		return (93 * seed + 101) % 256;
	};

	constexpr u16 randomlcg_u16(u16 seed) {
		return (16807 * seed + 10001) % 65536;
	};

	constexpr u32 randomlcg_u32(u32 seed) {
		return (1103515245 * u64(seed) + 1000001) % 4294967296;
	};

	constexpr u64 randomlcg_u64(u64 seed) {
		return 6364136223846793005 * seed + 100000001;
	};

	constexpr u8 quarter_u8(u8 seed) {
		seed = bitshuffle(seed);

		u8 q0 = (seed & 0x03);
		u8 q1 = (seed & 0x0c) >> 2;
		u8 q2 = (seed & 0x30) >> 4;
		u8 q3 = (seed & 0xc0) >> 6;

		return (q1 ^ q2 ^ q3) ^ ((q2 ^ q3 ^ q0) << 2) ^ ((q3 ^ q0 ^ q1) << 4) ^ ((q0 ^ q1 ^ q2) << 6);
	};

	constexpr u16 quarter_u16(u16 seed) {
		seed = bitshuffle(seed);

		u16 q0 = (seed & 0x000f);
		u16 q1 = (seed & 0x00f0) >> 4;
		u16 q2 = (seed & 0x0f00) >> 8;
		u16 q3 = (seed & 0xf000) >> 12;

		return (q1 ^ q2 ^ q3) ^ ((q2 ^ q3 ^ q0) << 4) ^ ((q3 ^ q0 ^ q1) << 8) ^ ((q0 ^ q1 ^ q2) << 12);
	};

	constexpr u32 quarter_u32(u32 seed) {
		seed = bitshuffle(seed);

		u32 q0 = (seed & 0x000000ff);
		u32 q1 = (seed & 0x0000ff00) >> 8;
		u32 q2 = (seed & 0x00ff0000) >> 16;
		u32 q3 = (seed & 0xff000000) >> 24;

		return (q1 ^ q2 ^ q3) ^ ((q2 ^ q3 ^ q0) << 8) ^ ((q3 ^ q0 ^ q1) << 16) ^ ((q0 ^ q1 ^ q2) << 24);
	};

	constexpr u64 quarter_u64(u64 seed) {
		seed = bitshuffle(seed);

		u64 q0 = (seed & 0x000000000000ffff);
		u64 q1 = (seed & 0x00000000ffff0000) >> 16;
		u64 q2 = (seed & 0x0000ffff00000000) >> 32;
		u64 q3 = (seed & 0xffff000000000000) >> 48;

		return (q1 ^ q2 ^ q3) ^ ((q2 ^ q3 ^ q0) << 16) ^ ((q3 ^ q0 ^ q1) << 32) ^ ((q0 ^ q1 ^ q2) << 48);
	};

	constexpr u8 eighth_u8(u8 seed) {
		seed = bitshuffle(seed);

		u8 e0 = (seed & 0x01);
		u8 e1 = (seed & 0x02) >> 1;
		u8 e2 = (seed & 0x04) >> 2;
		u8 e3 = (seed & 0x08) >> 3;
		u8 e4 = (seed & 0x10) >> 4;
		u8 e5 = (seed & 0x20) >> 5;
		u8 e6 = (seed & 0x40) >> 6;
		u8 e7 = (seed & 0x80) >> 7;

		return (e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7) ^ ((e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0) << 1) ^ ((e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1) << 2) ^ ((e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2) << 3) ^ ((e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3) << 4) ^ ((e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4) << 5) ^ ((e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5) << 6) ^ ((e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6) << 7);
	};

	constexpr u16 eighth_u16(u16 seed) {
		seed = bitshuffle(seed);

		u16 e0 = (seed & 0x0003);
		u16 e1 = (seed & 0x00c) >> 2;
		u16 e2 = (seed & 0x0030) >> 4;
		u16 e3 = (seed & 0x00c0) >> 6;
		u16 e4 = (seed & 0x0300) >> 8;
		u16 e5 = (seed & 0x0c00) >> 10;
		u16 e6 = (seed & 0x3000) >> 12;
		u16 e7 = (seed & 0xc000) >> 14;

		return (e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7) ^ ((e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0) << 2) ^ ((e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1) << 4) ^ ((e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2) << 6) ^ ((e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3) << 8) ^ ((e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4) << 10) ^ ((e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5) << 12) ^ ((e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6) << 14);
	};

	constexpr u32 eighth_u32(u32 seed) {
		seed = bitshuffle(seed);

		u32 e0 = (seed & 0x0000000f);
		u32 e1 = (seed & 0x000000f0) >> 4;
		u32 e2 = (seed & 0x00000f00) >> 8;
		u32 e3 = (seed & 0x0000f000) >> 12;
		u32 e4 = (seed & 0x000f0000) >> 16;
		u32 e5 = (seed & 0x00f00000) >> 20;
		u32 e6 = (seed & 0x0f000000) >> 24;
		u32 e7 = (seed & 0xf0000000) >> 28;

		return (e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7) ^ ((e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0) << 4) ^ ((e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1) << 8) ^ ((e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2) << 12) ^ ((e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3) << 16) ^ ((e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4) << 20) ^ ((e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5) << 24) ^ ((e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6) << 28);
	};

	constexpr u64 eighth_u64(u64 seed) {
		seed = bitshuffle(seed);

		u64 e0 = (seed & 0x00000000000000ff);
		u64 e1 = (seed & 0x000000000000ff00) >> 8;
		u64 e2 = (seed & 0x0000000000ff0000) >> 16;
		u64 e3 = (seed & 0x00000000ff000000) >> 24;
		u64 e4 = (seed & 0x000000ff00000000) >> 32;
		u64 e5 = (seed & 0x0000ff0000000000) >> 40;
		u64 e6 = (seed & 0x00ff000000000000) >> 48;
		u64 e7 = (seed & 0xff00000000000000) >> 56;

		return (e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7) ^ ((e2 ^ e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0) << 8) ^ ((e3 ^ e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1) << 16) ^ ((e4 ^ e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2) << 24) ^ ((e5 ^ e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3) << 32) ^ ((e6 ^ e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4) << 40) ^ ((e7 ^ e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5) << 48) ^ ((e0 ^ e1 ^ e2 ^ e3 ^ e4 ^ e5 ^ e6) << 56);
	};

	constexpr u8 deprime_u8(u8 seed) {
		u8 p_3 = seed % 3;
		seed /= 3;
		u8 p_5 = seed % 5;
		seed /= 5;
		u8 p_17 = seed % 17;

		p_3 = (2 * p_3 + 1) % 3;
		p_5 = (3 * p_5 + 1) % 5;
		p_17 = (11 * p_17 + 1) % 17;

		return (p_5 * 3 + p_3) * 17 + p_17;
	};

	constexpr u16 deprime_u16(u16 seed) {
		u16 p_3 = seed % 3;
		seed /= 3;
		u16 p_5 = seed % 5;
		seed /= 5;
		u16 p_17 = seed % 17;
		seed /= 17;
		u16 p_257 = seed % 257;

		p_3 = (2 * p_3 + 1) % 3;
		p_5 = (3 * p_5 + 1) % 5;
		p_17 = (11 * p_17 + 1) % 17;
		p_257 = (19 * p_257 + 1) % 257;

		return ((p_5 * 17 + p_17) * 3 + p_3) * 257 + p_257;
	};

	constexpr u32 deprime_u32(u32 seed) {
		u32 p_3 = seed % 3;
		seed /= 3;
		u32 p_5 = seed % 5;
		seed /= 5;
		u32 p_17 = seed % 17;
		seed /= 17;
		u32 p_257 = seed % 257;
		seed /= 257;
		u32 p_65537 = seed % 65537;

		p_3 = (2 * p_3 + 1) % 3;
		p_5 = (3 * p_5 + 1) % 5;
		p_17 = (11 * p_17 + 1) % 17;
		p_257 = (19 * p_257 + 1) % 257;
		p_65537 = (263 * p_65537 + 1) % 65537;

		return (((p_5 * 17 + p_17) * 257 + p_257) * 3 + p_3) * 65537 + p_65537;
	};

	constexpr u8 random_u8(u8 seed) {
		return quarter_u8(deprime_u8(seed));
	};

	constexpr u16 random_u16(u16 seed) {
		return quarter_u16(deprime_u16(seed));
	};

	constexpr u32 random_u32(u32 seed) {
		return quarter_u32(deprime_u32(seed));
	};

	constexpr s8 random_s8(u8 seed) {
		return s16(random_u8(seed)) - 128;
	};

	constexpr s16 random_s16(u16 seed) {
		return s32(random_u16(seed)) - 32768;
	};

	constexpr s32 random_s32(u32 seed) {
		return s64(random_u32(seed)) - 2147483648;
	};

	constexpr float random_ufloat(u32 seed) {
		return float(random_u32(seed)) / float(random_u32(~seed));
	};

	constexpr float random_sfloat(u32 seed) {
		return float(random_s32(seed)) / float(random_s32(~seed));
	};

	constexpr float random_float(u32 seed) {
		return afract(float(random_u32(seed)) / float(random_u32(std::rotl(seed, 16))));
	};
};