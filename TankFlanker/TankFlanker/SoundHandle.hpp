﻿#pragma once
#include <DxLib.h>
#include <string_view>
#include <algorithm>
class SoundHandle {
private:
	int handle_;
	constexpr SoundHandle(int h) noexcept : handle_(h) {}
	static constexpr int invalid_handle = -1;

public:
	constexpr SoundHandle() noexcept : handle_(invalid_handle) {}
	SoundHandle(const SoundHandle&) = delete;
	SoundHandle(SoundHandle&& o) noexcept : handle_(o.handle_) {
		o.handle_ = invalid_handle;
	}
	SoundHandle& operator=(const SoundHandle&) = delete;
	SoundHandle& operator=(SoundHandle&& o) noexcept {
		this->handle_ = o.handle_;
		o.handle_ = invalid_handle;
		return *this;
	}
	~SoundHandle() noexcept {
		if (-1 != this->handle_) {
			DeleteSoundMem(this->handle_);
		}
	}
	void Dispose() noexcept {
		if (-1 != this->handle_) {
			DeleteSoundMem(this->handle_);
			this->handle_ = -1;
		}
	}
	int get() const noexcept { return handle_; }
	SoundHandle Duplicate() const noexcept { return DxLib::DuplicateSoundMem(this->handle_); }

	bool play(int type, int flag=1) const noexcept { return (PlaySoundMem(handle_, type, flag) == 0);}
	bool stop() const noexcept { return (StopSoundMem(handle_) == 0); }
	bool vol(int vol) const noexcept { return (ChangeVolumeSoundMem(std::clamp<int>(vol,0,255),handle_) == 0); }

	static SoundHandle Load(std::basic_string_view<TCHAR> FileName, int BufferNum = 3) noexcept {
		return { DxLib::LoadSoundMemWithStrLen(FileName.data(), FileName.length(), BufferNum) };
	}
};
