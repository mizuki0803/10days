#pragma once
#include "ObjObject3d.h"

/// <summary>
/// á‚¾‚é‚Ü(‰º)
/// </summary>
class SnowManUnder : public ObjObject3d
{
public: //Ã“Iƒƒ“ƒoŠÖ”
	/// <summary>
	/// ¶¬ˆ—
	/// </summary>
	/// <param name="model">ƒ‚ƒfƒ‹</param>
	/// <returns>á‚¾‚é‚Ü(‰º)</returns>
	static SnowManUnder* Create(ObjModel* model, const Vector3& position, const Vector3& scale);
};
