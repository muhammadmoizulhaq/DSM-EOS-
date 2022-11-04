// MIT License
//
// Copyright (c) 2019, Muhammad Moiz ul haq
// All rights reserved.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// [comment.type]
//  always use the C++ style and not the C /**/ style
//  because it shows up in searches
//  Visual Studio shortcut to toggle comments on a block:
//      Edit -> Advanced -> Un/Comment Selection
//      Ctrl+K Ctrl+C / Ctrl+K Ctrl+U
// 
// [header.incl.order.cpp]
//  Generally speaking the include order of files in .cpp's should be
#include "EOSNetworkManager.h"			// 1) the equivalent header file
// 2) Engine files
// 3) MMUH Core files
// 4) Shared or Feature files
// 5) Local files

void UEOSNetworkManager::InitEOSPlatform()
{
	// Create platform instance
	EOS_Platform_Options PlatformOptions = {};
	PlatformOptions.ApiVersion = EOS_PLATFORM_OPTIONS_API_LATEST;
	PlatformOptions.bIsServer = IsRunningDedicatedServer();
}

UEOSNetworkManager* UEOSNetworkManager::IntEOSNetworkManager()
{
	return NewObject<UEOSNetworkManager>();
}