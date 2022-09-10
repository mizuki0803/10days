#pragma once
#include "Obstacle.h"

/// <summary>
/// –Ø
/// </summary>
class Tree : public Obstacle
{
public: //Ã“Iƒƒ“ƒoŠÖ”
	/// <summary>
	/// ¶¬ˆ—
	/// </summary>
	/// <param name="model">ƒ‚ƒfƒ‹</param>
	/// <returns>–Ø</returns>
	static Tree* Create(ObjModel* model, const Vector3& position);
};
