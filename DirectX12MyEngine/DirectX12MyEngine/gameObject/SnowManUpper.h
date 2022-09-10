#pragma once
#include "ObjObject3d.h"

/// <summary>
/// á‚¾‚é‚Ü(ã)
/// </summary>
class SnowManUpper : public ObjObject3d
{
public: //Ã“Iƒƒ“ƒoŠÖ”
	/// <summary>
	/// ¶¬ˆ—
	/// </summary>
	/// <param name="model">ƒ‚ƒfƒ‹</param>
	/// <returns>á‚¾‚é‚Ü(ã)</returns>
	static SnowManUpper* Create(ObjModel* model, const Vector3& position, const Vector3& scale);
};
