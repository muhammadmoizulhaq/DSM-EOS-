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

// [header.guard] include guard
#pragma once

// [Header.third.party.incl] Third Party Include file here
#include "EOSCore/Include/eos_sdk.h"

// [basic.rule] FOLLOW UE4 coding style! 
//  https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/
//  especially here in the header/interface
//  in the implementation (.cpp) you are allowed to diverge a bit for personal taste
//  but NEVER when it comes to things that will be visible from outside
//  aka public variables, functions, names etc

// [basic.language] Use US English for all names and comments
//  BAD -> FColor SpecialisedColour;
//  GOOD -> FColor SpecializedColor;

// [header.iwyu] we shall use IWYU 
//  https://docs.unrealengine.com/latest/INT/Programming/BuildTools/UnrealBuildTool/IWYU/index.html
#include <CoreMinimal.h>

// [header.engine.incl] list all the Engine dependencies with angle brackets includes
#include <UObject/NoExportTypes.h>

// [header.incl.order]
//  Generally speaking the include order of files should be:
//  1) CoreMinimal
//  2) Other Engine files
//  3) MMUH Core files
//  4) local includes - with "" style
//  5) this file .generate.h - with "" style

// [header.incl.privatepath]
//  Never include private paths in a public header file. This can cause hard to track linker
//  or compiler errors at a later date. Either re-factor your code so that you can use a forward
//  declare or, if necessary, make the file you are trying to include public.

// [header.incl.gen] always have the .generated files last
#include "EOSNetworkManager.generated.h"

UCLASS()
class EPICONLINESERVICECORE_API UEOSNetworkManager : public UObject
{
	GENERATED_BODY()

	// do not write tha default constructor/distructor for the classes containing GENERATED_BODY() Macro
	// due to that macro works default constructor/distructor could case crashes
	// 
	// [class.virtual] any virtual method declaration must specify one, and only one, of the following:
	//  - `virtual` for declaration of a new virtual method
	//  - `override` for overriding an existing virtual method
	//  - `final` for overrides that allow no further overriding
	//  `final` should be used with care as it can have large ramifications on downstream classes.
	// 
	// [class.same-line] DON'T write definitions on the same line as declarations!
	//  it makes debugging impossible
	// [class.inline.bad] NEVER USE `inline or `FORCEINLINE` inside a class declaration
	//  - it's useless and leads to linking errors
	//  - definitions(bodies) inside a class/struct are implicitly inline!
	// [comment.useless] DON'T write meaningless comments!
	//  they should always reflect bigger purpose or reveal hidden details
	// 
	// [class.order] Do not alternate between functions and variables in the class declaration
	//  Put all functions first, all variables last
	// 
	// [ue.ecs.split] Split functionality into components
	//  avoid creating monolithic giant classes!
	// 
	// [ue.ecs.gc] never use naked pointers to UObject's, always have UPROPERTY or UE smart ptr
	//  Generally, for storing pointers to classes you don't own, use TWeakObjectPtr.
	//
	//  Generally, for storing pointers to classes you do own, use UPROPERTY().
public:
	/**
	* Initialize Network Manager
	* It sould be called before using other functionalities
	* 
	* @return it return's a Pointer Object
	*/
	UFUNCTION(BlueprintCallable, Category = "Epic Online Services Core | Init")
	/*static const*/UEOSNetworkManager* IntEOSNetworkManager();
};