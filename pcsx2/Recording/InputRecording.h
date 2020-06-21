/*  PCSX2 - PS2 Emulator for PCs
 *  Copyright (C) 2002-2020  PCSX2 Dev Team
 *
 *  PCSX2 is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesser General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  PCSX2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with PCSX2.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "InputRecordingFile.h"


#ifndef DISABLE_RECORDING
class InputRecording
{
public:
	// Main handler for ingesting input data and either saving it to the recording file (recording)
	// or mutating it to the contents of the recording file (replaying)
	void ControllerInterrupt(u8 &data, u8 &port, u16 &BufCount, u8 buf[]);

	// The running frame counter for the input recording
	u32 GetFrameCounter();

	InputRecordingFile &GetInputRecordingData();

	// The internal PCSX2 g_FrameCount value on the first frame of the recording
	u32 GetStartingFrame();

	void IncrementFrameCounter();

	// DEPRECATED: Slated for removal 
	// If the current frame contains controller / input data
	bool IsInterruptFrame();

	// If there is currently an input recording being played back or actively being recorded
	bool RecordingActive();
    bool IsRecordingReplaying();

	// String representation of the current recording mode to be interpolated into the title
	wxString RecordingModeTitleSegment();

	// Switches between recording and replaying the active input recording file
	void RecordModeToggle();

	// Set the running frame counter for the input recording to an arbitrary value
	void SetFrameCounter(u32 newFrameCounter);
	// Store the starting internal PCSX2 g_FrameCount value
	void SetStartingFrame(u32 newStartingFrame);
	
	/// Functions called from GUI

	// Create a new input recording file
	void Create(wxString filename, bool fromSaveState, wxString authorName);
	// Play an existing input recording from a file
	void Play(wxString filename, bool fromSaveState);
	// Stop the active input recording
	void Stop();

private:
	enum class InputRecordingMode {
		NoneActive,
		Recording,
		Replaying,
	};

	bool fInterruptFrame = false;
	InputRecordingFile inputRecordingData;
	InputRecordingMode state = InputRecording::InputRecordingMode::NoneActive;
	u32 frameCounter = 0;
    u32 startingFrame = -1;
};

extern InputRecording g_InputRecording;
#endif
