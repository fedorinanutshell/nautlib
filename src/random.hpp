#ifndef XORSHIFT_INCLUDED
#define XORSHIFT_INCLUDED

#include "base.hpp"

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
		u32 x = (val << 32) | (val >> 32);
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

	constexpr u8 random_u8(u8 seed) {
		return randombit_u8(randomlcg_u8(seed));
	};

	constexpr u16 random_u16(u16 seed) {
		return randombit_u16(randomlcg_u16(seed));
	};

	constexpr u32 random_u32(u32 seed) {
		return randombit_u32(randomlcg_u32(seed));
	};

	constexpr u64 random_u64(u64 seed) {
		return randombit_u64(randomlcg_u64(seed));
	};
};

#endif