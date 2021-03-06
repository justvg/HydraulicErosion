#pragma once

#include <math.h>
#include <stdint.h>

#define PI 3.14159265358979323846f

#define Epsilon (1.19e-7f)
#define int32_t_MIN (-2147483647 - 1)
#define int32_t_MAX 2147483647
#define UINT32_MAX 0xFFFFFFFF
#define FLT_MAX 3.402823466e+38F

union vec2
{
	struct
	{
		float x, y;
	};

	struct
	{
		float u, v;
	};

	float E[2];

	vec2() { x = y = 0.0f; }
	vec2(float X, float Y) { x = X; y = Y; }
};

union vec3
{
	struct
	{
		float x, y, z;
	};

	struct
	{
		float u, v, w;
	};

	struct
	{
		float r, g, b;
	};

	struct
	{
		vec2 xy;
		float Ignored_0;
	};
	struct
	{
		float Ignored_1;
		vec2 yz;
	};
	struct
	{
		vec2 uv;
		float Ignored_2;
	};
	struct
	{
		float Ignored_3;
		vec2 vw;
	};

	float E[3];

	vec3() {}
	vec3(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	vec3(vec2 XY, float Z) { x = XY.x; y = XY.y; z = Z; }
};

union vec4
{
	struct
	{
		float x, y, z, w;
	};

	struct
	{
		float r, g, b, a;
	};

	struct
	{
		vec3 xyz;
		float Ignored_0;
	};
	struct
	{
		vec2 xy;
		float Ignored_1;
		float Ignored_2;
	};
	struct
	{
		float Ignored_3;
		vec2 yz;
		float Ignored_4;
	};
	struct
	{
		float Ignored_5;
		float Ignored_6;
		vec2 zw;
	};

	struct
	{
		vec3 rgb;
		float Ignored_7;
	};

	float E[4];

	vec4() {}
	vec4(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; }
};

inline vec2
vec2i(int32_t X, int32_t Y)
{
	vec2 Result = vec2((float)X, (float)Y);

	return(Result);
}

inline vec2
vec2i(uint32_t X, uint32_t Y)
{
	vec2 Result = vec2((float)X, (float)Y);

	return(Result);
}

inline vec3
vec3i(int32_t X, int32_t Y, int32_t Z)
{
	vec3 Result = vec3((float)X, (float)Y, (float)Z);

	return(Result);
}

inline vec3
vec3i(uint32_t X, uint32_t Y, uint32_t Z)
{
	vec3 Result = vec3((float)X, (float)Y, (float)Z);

	return(Result);
}

inline vec4
vec4i(int32_t X, int32_t Y, int32_t Z, int32_t W)
{
	vec4 Result = vec4((float)X, (float)Y, (float)Z, (float)W);

	return(Result);
}

inline vec4
vec4i(uint32_t X, uint32_t Y, uint32_t Z, uint32_t W)
{
	vec4 Result = vec4((float)X, (float)Y, (float)Z, (float)W);

	return(Result);
}

union mat2
{
	float E[4];
	struct
	{
		float a11, a21;
		float a12, a22;
	};
};

union mat3
{
	float E[9];
	struct
	{
		float a11, a21, a31;
		float a12, a22, a32;
		float a13, a23, a33;
	};
};

union mat4
{
	float E[16];

	struct
	{
		float a11, a21, a31, a41;
		float a12, a22, a32, a42;
		float a13, a23, a33, a43;
		float a14, a24, a34, a44;
	};
};

inline float
Square(float Value)
{
	Value = Value * Value;
	return(Value);
}

inline float
SquareRoot(float Value)
{
	Value = sqrt(Value);
	return(Value);
}

inline float
Absolute(float Value)
{
	if (Value < 0.0f) Value = -Value;
	return(Value);
}

inline uint32_t
Absolute(int32_t Value)
{
	if (Value < 0) Value = -Value;
	return((uint32_t)Value);
}

inline int32_t
FloorReal32ToInt32(float Value)
{
	int32_t Result = (int32_t)Value;
	if ((float)Result > Value)
	{
		--Result;
	}

	return(Result);
}

inline float
Radians(float Angle)
{
	float Result = (Angle / 180.0f) * PI;;

	return(Result);
}

inline float
Degrees(float Rad)
{
	float Result = (Rad / PI) * 180.0f;

	return(Result);
}

inline float
Cos(float Rad)
{
	float Result = cosf(Rad);
	return(Result);
}

inline float
Sin(float Rad)
{
	float Result = sinf(Rad);
	return(Result);
}

inline float
Tan(float Rad)
{
	float Result = tanf(Rad);
	return(Result);
}

inline float
Lerp(float A, float B, float t)
{
	float Result = A + (B - A) * t;

	return(Result);
}

inline float
Clamp(float Value, float Min, float Max)
{
	if (Min > Max)
	{
		float Temp = Min;
		Min = Max;
		Max = Temp;
	}

	if (Value < Min) Value = Min;
	else if (Value > Max) Value = Max;

	return(Value);
}

inline float
Min(float A, float B)
{
	float Result = (A < B) ? A : B;
	return(Result);
}

inline float
Max(float A, float B)
{
	float Result = (A > B) ? A : B;
	return(Result);
}

// 
// NOTE(georgy): vec2
// 

inline vec2
operator+ (vec2 A, vec2 B)
{
	vec2 Result;

	Result.x = A.x + B.x;
	Result.y = A.y + B.y;

	return(Result);
}

inline vec2
operator- (vec2 A, vec2 B)
{
	vec2 Result;

	Result.x = A.x - B.x;
	Result.y = A.y - B.y;

	return(Result);
}

inline vec2
Hadamard(vec2 A, vec2 B)
{
	vec2 Result;

	Result.x = A.x * B.x;
	Result.y = A.y * B.y;

	return(Result);
}

inline vec2
operator* (vec2 A, float B)
{
	vec2 Result;

	Result.x = A.x * B;
	Result.y = A.y * B;

	return(Result);
}

inline vec2
operator* (float B, vec2 A)
{
	vec2 Result = A * B;

	return(Result);
}

inline vec2&
operator+= (vec2& A, vec2 B)
{
	A = A + B;

	return(A);
}

inline vec2&
operator-= (vec2& A, vec2 B)
{
	A = A - B;

	return(A);
}

inline vec2&
operator*= (vec2& A, float B)
{
	A = A * B;

	return(A);
}

inline vec2
operator- (vec2 A)
{
	vec2 Result;

	Result.x = -A.x;
	Result.y = -A.y;

	return(Result);
}

inline float
Dot(vec2 A, vec2 B)
{
	float Result = A.x * B.x + A.y * B.y;

	return(Result);
}

inline float
LengthSq(vec2 A)
{
	float Result = Dot(A, A);

	return(Result);
}

inline float
Length(vec2 A)
{
	float Result = sqrtf(LengthSq(A));

	return(Result);
}

inline vec2
Normalize(vec2 A)
{
	vec2 Result = A * (1.0f / Length(A));

	return(Result);
}

inline vec2
NOZ(vec2 A)
{
	vec2 Result;

	float Len = Length(A);
	if (Len <= Epsilon)
	{
		Result = vec2(0.0f, 0.0f);
	}
	else
	{
		Result = A * (1.0f / Length(A));
	}

	return(Result);
}

inline vec2
Perp(vec2 A)
{
	vec2 Result = vec2(-A.y, A.x);

	return(Result);
}

inline float
Cross2D(vec2 A, vec2 B)
{
	float Result = Dot(Perp(A), B);

	return(Result);
}

inline vec2
Lerp(vec2 A, vec2 B, float t)
{
	vec2 Result = A + (B - A) * t;

	return(Result);
}

inline bool
VectorsAreEqual(vec2 A, vec2 B)
{
	bool XIsEqual = (Absolute(A.x - B.x) <= Epsilon);
	bool YIsEqual = (Absolute(A.y - B.y) <= Epsilon);

	return(XIsEqual && YIsEqual);
}

// 
// NOTE(georgy): vec3
// 

inline vec3
operator+ (vec3 A, vec3 B)
{
	vec3 Result;

	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;

	return(Result);
}

inline vec3
operator- (vec3 A, vec3 B)
{
	vec3 Result;

	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;

	return(Result);
}

inline vec3
Hadamard(vec3 A, vec3 B)
{
	vec3 Result;

	Result.x = A.x * B.x;
	Result.y = A.y * B.y;
	Result.z = A.z * B.z;

	return(Result);
}

inline vec3
operator* (vec3 A, float B)
{
	vec3 Result;

	Result.x = A.x * B;
	Result.y = A.y * B;
	Result.z = A.z * B;

	return(Result);
}

inline vec3
operator* (float B, vec3 A)
{
	vec3 Result = A * B;

	return(Result);
}

inline vec3&
operator+= (vec3& A, vec3 B)
{
	A = A + B;

	return(A);
}

inline vec3&
operator-= (vec3& A, vec3 B)
{
	A = A - B;

	return(A);
}

inline vec3&
operator*= (vec3& A, float B)
{
	A = A * B;

	return(A);
}

inline vec3
operator- (vec3 A)
{
	vec3 Result;

	Result.x = -A.x;
	Result.y = -A.y;
	Result.z = -A.z;

	return(Result);
}

inline float
Dot(vec3 A, vec3 B)
{
	float Result = A.x * B.x + A.y * B.y + A.z * B.z;

	return(Result);
}

inline float
LengthSq(vec3 A)
{
	float Result = Dot(A, A);

	return(Result);
}

inline float
Length(vec3 A)
{
	float Result = sqrtf(LengthSq(A));

	return(Result);
}

inline vec3
Normalize(vec3 A)
{
	vec3 Result = A * (1.0f / Length(A));

	return(Result);
}

inline vec3
NOZ(vec3 A)
{
	vec3 Result;

	float Len = Length(A);
	if (Len <= Epsilon)
	{
		Result = vec3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		Result = A * (1.0f / Length(A));
	}

	return(Result);
}

inline vec3
Cross(vec3 A, vec3 B)
{
	vec3 Result;

	Result.x = A.y * B.z - B.y * A.z;
	Result.y = A.z * B.x - B.z * A.x;
	Result.z = A.x * B.y - B.x * A.y;

	return(Result);
}

inline vec3
Lerp(vec3 A, vec3 B, float t)
{
	vec3 Result = A + (B - A) * t;

	return(Result);
}

// 
// NOTE(georgy): vec4
// 

inline vec4
operator+ (vec4 A, vec4 B)
{
	vec4 Result;

	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;
	Result.w = A.w + B.w;

	return(Result);
}

inline vec4
operator- (vec4 A, vec4 B)
{
	vec4 Result;

	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;
	Result.w = A.w - B.w;

	return(Result);
}

inline vec4
Hadamard(vec4 A, vec4 B)
{
	vec4 Result;

	Result.x = A.x * B.x;
	Result.y = A.y * B.y;
	Result.z = A.z * B.z;
	Result.w = A.w * B.w;

	return(Result);
}

inline vec4
operator* (vec4 A, float B)
{
	vec4 Result;

	Result.x = A.x * B;
	Result.y = A.y * B;
	Result.z = A.z * B;
	Result.w = A.w * B;

	return(Result);
}

inline vec4
operator* (float B, vec4 A)
{
	vec4 Result = A * B;

	return(Result);
}

inline vec4&
operator+= (vec4& A, vec4 B)
{
	A = A + B;

	return(A);
}

inline vec4&
operator-= (vec4& A, vec4 B)
{
	A = A - B;

	return(A);
}

inline vec4&
operator*= (vec4& A, float B)
{
	A = A * B;

	return(A);
}

inline vec4
operator- (vec4 A)
{
	vec4 Result;

	Result.x = -A.x;
	Result.y = -A.y;
	Result.z = -A.z;
	Result.w = -A.w;

	return(Result);
}

inline float
Dot(vec4 A, vec4 B)
{
	float Result = A.x * B.x + A.y * B.y + A.z * B.z + A.w * B.w;

	return(Result);
}

inline float
LengthSq(vec4 A)
{
	float Result = Dot(A, A);

	return(Result);
}

inline float
Length(vec4 A)
{
	float Result = sqrtf(LengthSq(A));

	return(Result);
}

inline vec4
Normalize(vec4 A)
{
	vec4 Result = A * (1.0f / Length(A));

	return(Result);
}

inline vec4
Lerp(vec4 A, vec4 B, float t)
{
	vec4 Result = A + (B - A) * t;

	return(Result);
}

// 
// NOTE(georgy): mat2
// 

static mat2
Rotation2x2(float Angle)
{
	mat2 Result;

	float Rad = Radians(Angle);
	vec2 XAxis = vec2(Cos(Rad), Sin(Rad));
	vec2 YAxis = Perp(XAxis);

	Result.a11 = XAxis.x;
	Result.a21 = XAxis.y;
	Result.a12 = YAxis.x;
	Result.a22 = YAxis.y;

	return(Result);
}

inline vec2
operator*(mat2 M, vec2 V)
{
	vec2 Result;

	Result.x = M.a11 * V.x + M.a12 * V.y;
	Result.y = M.a21 * V.x + M.a22 * V.y;

	return(Result);
}

// 
// NOTE(georgy): mat3
// 

inline mat3
Identity3x3(float Diagonal = 1.0f)
{
	mat3 Result = {};

	Result.a11 = Diagonal;
	Result.a22 = Diagonal;
	Result.a33 = Diagonal;

	return(Result);
}

inline mat3
Scaling3x3(float Scale)
{
	mat3 Result = {};

	Result.a11 = Scale;
	Result.a22 = Scale;
	Result.a33 = Scale;

	return(Result);
}

inline mat3
Scaling3x3(vec3 Scale)
{
	mat3 Result = {};

	Result.a11 = Scale.x;
	Result.a22 = Scale.y;
	Result.a33 = Scale.z;

	return(Result);
}

static mat3
Rotation3x3(float Angle, vec3 Axis)
{
	mat3 Result;

	float Rad = Radians(Angle);
	float Sine = Sin(Rad);
	float Cosine = Cos(Rad);

	Axis = NOZ(Axis);
	if ((Axis.x == 0.0f) && (Axis.y == 0.0f) && (Axis.z == 0.0f))
	{
		Result = Identity3x3();
	}
	else
	{
		Result.a11 = Axis.x * Axis.x * (1.0f - Cosine) + Cosine;
		Result.a21 = Axis.x * Axis.y * (1.0f - Cosine) + Axis.z * Sine;
		Result.a31 = Axis.x * Axis.z * (1.0f - Cosine) - Axis.y * Sine;

		Result.a12 = Axis.x * Axis.y * (1.0f - Cosine) - Axis.z * Sine;
		Result.a22 = Axis.y * Axis.y * (1.0f - Cosine) + Cosine;
		Result.a32 = Axis.y * Axis.z * (1.0f - Cosine) + Axis.x * Sine;

		Result.a13 = Axis.x * Axis.z * (1.0f - Cosine) + Axis.y * Sine;
		Result.a23 = Axis.y * Axis.z * (1.0f - Cosine) - Axis.x * Sine;
		Result.a33 = Axis.z * Axis.z * (1.0f - Cosine) + Cosine;
	}

	return(Result);
}

static mat3
Transpose3x3(const mat3& M)
{
	mat3 Result;

	Result.a11 = M.a11;
	Result.a21 = M.a12;
	Result.a31 = M.a13;

	Result.a12 = M.a21;
	Result.a22 = M.a22;
	Result.a32 = M.a23;

	Result.a13 = M.a31;
	Result.a23 = M.a32;
	Result.a33 = M.a33;

	return(Result);
}

static mat3
Inverse3x3(const mat3& M)
{
	mat3 InverseMatrix = {};

	float Determinant = M.a11 * M.a22 * M.a33 + M.a12 * M.a23 * M.a31 + M.a13 * M.a21 * M.a32 -
		(M.a31 * M.a22 * M.a13 + M.a32 * M.a23 * M.a11 + M.a33 * M.a21 * M.a12);
	if (Determinant > Epsilon)
	{
		float OneOverDeterminant = 1.0f / Determinant;

		InverseMatrix.a11 = (M.a22 * M.a33 - M.a32 * M.a23) * OneOverDeterminant;
		InverseMatrix.a12 = (-(M.a21 * M.a33 - M.a31 * M.a23)) * OneOverDeterminant;
		InverseMatrix.a13 = (M.a21 * M.a32 - M.a31 * M.a22) * OneOverDeterminant;
		InverseMatrix.a21 = (-(M.a12 * M.a33 - M.a32 * M.a13)) * OneOverDeterminant;
		InverseMatrix.a22 = (M.a11 * M.a33 - M.a31 * M.a13) * OneOverDeterminant;
		InverseMatrix.a23 = (-(M.a11 * M.a32 - M.a31 * M.a12)) * OneOverDeterminant;
		InverseMatrix.a31 = (M.a12 * M.a23 - M.a22 * M.a13) * OneOverDeterminant;
		InverseMatrix.a32 = (-(M.a11 * M.a23 - M.a21 * M.a13)) * OneOverDeterminant;
		InverseMatrix.a33 = (M.a11 * M.a22 - M.a21 * M.a12) * OneOverDeterminant;

		InverseMatrix = Transpose3x3(InverseMatrix);
	}

	return(InverseMatrix);
}

static mat3
operator*(mat3 A, mat3 B)
{
	mat3 Result;

	for (uint32_t Row = 0;
		Row < 3;
		Row++)
	{
		for (uint32_t Column = 0;
			Column < 3;
			Column++)
		{
			float Sum = 0.0f;
			for (uint32_t E = 0;
				E < 3;
				E++)
			{
				Sum += A.E[Row + E * 3] * B.E[Column * 3 + E];
			}
			Result.E[Row + Column * 3] = Sum;
		}
	}

	return(Result);
}

static vec3
operator*(mat3 A, vec3 B)
{
	vec3 Result;

	Result.x = A.a11 * B.x + A.a12 * B.y + A.a13 * B.z;
	Result.y = A.a21 * B.x + A.a22 * B.y + A.a23 * B.z;
	Result.z = A.a31 * B.x + A.a32 * B.y + A.a33 * B.z;

	return(Result);
}

// 
// NOTE(georgy): mat4
// 

inline mat4
Identity(float Diagonal = 1.0f)
{
	mat4 Result = {};

	Result.a11 = Diagonal;
	Result.a22 = Diagonal;
	Result.a33 = Diagonal;
	Result.a44 = Diagonal;

	return(Result);
}

inline mat4
Translation(vec3 Translate)
{
	mat4 Result = Identity(1.0f);

	Result.a14 = Translate.x;
	Result.a24 = Translate.y;
	Result.a34 = Translate.z;

	return(Result);
}

inline mat4
Scaling(float Scale)
{
	mat4 Result = {};

	Result.a11 = Scale;
	Result.a22 = Scale;
	Result.a33 = Scale;
	Result.a44 = 1.0f;

	return(Result);
}

inline mat4
Scaling(vec3 Scale)
{
	mat4 Result = {};

	Result.a11 = Scale.x;
	Result.a22 = Scale.y;
	Result.a33 = Scale.z;
	Result.a44 = 1.0f;

	return(Result);
}

static mat4
Rotation(float Angle, vec3 Axis)
{
	mat4 Result;

	float Rad = Radians(Angle);
	float Sine = Sin(Rad);
	float Cosine = Cos(Rad);

	Axis = Normalize(Axis);

	Result.a11 = Axis.x * Axis.x * (1.0f - Cosine) + Cosine;
	Result.a21 = Axis.x * Axis.y * (1.0f - Cosine) + Axis.z * Sine;
	Result.a31 = Axis.x * Axis.z * (1.0f - Cosine) - Axis.y * Sine;
	Result.a41 = 0.0f;

	Result.a12 = Axis.x * Axis.y * (1.0f - Cosine) - Axis.z * Sine;
	Result.a22 = Axis.y * Axis.y * (1.0f - Cosine) + Cosine;
	Result.a32 = Axis.y * Axis.z * (1.0f - Cosine) + Axis.x * Sine;
	Result.a42 = 0.0f;

	Result.a13 = Axis.x * Axis.z * (1.0f - Cosine) + Axis.y * Sine;
	Result.a23 = Axis.y * Axis.z * (1.0f - Cosine) - Axis.x * Sine;
	Result.a33 = Axis.z * Axis.z * (1.0f - Cosine) + Cosine;
	Result.a43 = 0.0f;

	Result.a14 = 0.0f;
	Result.a24 = 0.0f;
	Result.a34 = 0.0f;
	Result.a44 = 1.0f;

	return(Result);
}

static mat4
Mat4(const mat3& M)
{
	mat4 Result;

	Result.a11 = M.a11;
	Result.a21 = M.a21;
	Result.a31 = M.a31;
	Result.a12 = M.a12;
	Result.a22 = M.a22;
	Result.a32 = M.a32;
	Result.a13 = M.a13;
	Result.a23 = M.a23;
	Result.a33 = M.a33;
	Result.a41 = Result.a42 = Result.a43 = Result.a14 = Result.a24 = Result.a34 = 0.0f;
	Result.a44 = 1.0f;

	return(Result);
}

static mat4
LookAt(vec3 From, vec3 Target, vec3 UpAxis = vec3(0.0f, 1.0f, 0.0f))
{
	vec3 Forward = Normalize(From - Target);
	vec3 Right = Normalize(Cross(UpAxis, Forward));
	vec3 Up = Cross(Forward, Right);

	mat4 Result;

	Result.a11 = Right.x;
	Result.a21 = Up.x;
	Result.a31 = Forward.x;
	Result.a41 = 0.0f;

	Result.a12 = Right.y;
	Result.a22 = Up.y;
	Result.a32 = Forward.y;
	Result.a42 = 0.0f;

	Result.a13 = Right.z;
	Result.a23 = Up.z;
	Result.a33 = Forward.z;
	Result.a43 = 0.0f;

	Result.a14 = -Dot(Right, From);
	Result.a24 = -Dot(Up, From);
	Result.a34 = -Dot(Forward, From);
	Result.a44 = 1.0f;

	return(Result);
}

static mat4
ViewRotationMatrixFromDirection(vec3 Dir, vec3 UpAxis = vec3(0.0f, 1.0f, 0.0f))
{
	vec3 Forward = Normalize(-Dir);
	vec3 Right = Normalize(Cross(UpAxis, Forward));
	vec3 Up = Cross(Forward, Right);

	mat4 Result;

	Result.a11 = Right.x;
	Result.a21 = Up.x;
	Result.a31 = Forward.x;
	Result.a41 = 0.0f;

	Result.a12 = Right.y;
	Result.a22 = Up.y;
	Result.a32 = Forward.y;
	Result.a42 = 0.0f;

	Result.a13 = Right.z;
	Result.a23 = Up.z;
	Result.a33 = Forward.z;
	Result.a43 = 0.0f;

	Result.a14 = 0.0f;
	Result.a24 = 0.0f;
	Result.a34 = 0.0f;
	Result.a44 = 1.0f;

	return(Result);
}

static mat4
Ortho(float Bottom, float Top, float Left, float Right, float Near, float Far)
{
	mat4 Result = {};

	Result.a11 = 2.0f / (Right - Left);
	Result.a22 = 2.0f / (Top - Bottom);
	Result.a33 = -2.0f / (Far - Near);
	Result.a14 = -(Right + Left) / (Right - Left);
	Result.a24 = -(Top + Bottom) / (Top - Bottom);
	Result.a34 = -(Far + Near) / (Far - Near);
	Result.a44 = 1.0f;

	return(Result);
}

static mat4
Perspective(float FoV, float AspectRatio, float Near, float Far)
{
	float Scale = Tan(Radians(FoV) * 0.5f) * Near;
	float Top = Scale;
	float Bottom = -Top;
	float Right = Scale * AspectRatio;
	float Left = -Right;

	mat4 Result = {};

	Result.a11 = 2.0f * Near / (Right - Left);
	Result.a22 = 2.0f * Near / (Top - Bottom);
	Result.a13 = (Right + Left) / (Right - Left);
	Result.a23 = (Top + Bottom) / (Top - Bottom);
	Result.a33 = -(Far + Near) / (Far - Near);
	Result.a43 = -1.0f;
	Result.a34 = -(2.0f * Far * Near) / (Far - Near);

	return(Result);
}

static mat4
operator*(mat4 A, mat4 B)
{
	mat4 Result;

	for (uint32_t Row = 0;
		Row < 4;
		Row++)
	{
		for (uint32_t Column = 0;
			Column < 4;
			Column++)
		{
			float Sum = 0.0f;
			for (uint32_t E = 0;
				E < 4;
				E++)
			{
				Sum += A.E[Row + E * 4] * B.E[Column * 4 + E];
			}
			Result.E[Row + Column * 4] = Sum;
		}
	}

	return(Result);
}

static vec4
operator*(mat4 A, vec4 B)
{
	vec4 Result;

	Result.x = A.a11 * B.x + A.a12 * B.y + A.a13 * B.z + A.a14 * B.w;
	Result.y = A.a21 * B.x + A.a22 * B.y + A.a23 * B.z + A.a24 * B.w;
	Result.z = A.a31 * B.x + A.a32 * B.y + A.a33 * B.z + A.a34 * B.w;
	Result.w = A.a41 * B.x + A.a42 * B.y + A.a43 * B.z + A.a44 * B.w;

	return(Result);
}

// 
// NOTE(georgy): Noise
// 

// NOTE(georgy): Must pe a power of 2!
static vec2 Gradients2D[8] =
{
	vec2(0.0f, 1.0f),
	vec2(-0.7071f, 0.7071f),
	vec2(-1.0f, 0.0f),
	vec2(-0.7071f, -0.7071f),
	vec2(0.0f, -1.0f),
	vec2(0.7071f, -0.7071f),
	vec2(1.0f, 0.0f),
	vec2(0.7071f, 0.7071f)
};

// NOTE(georgy): Must be a power of 2!
static vec3 Gradients3D[16] =
{
	vec3(0.7071f,0.7071f, 0.0f),
	vec3(-0.7071f, 0.7071f, 0.0f),
	vec3(0.7071f, -0.7071f, 0.0f),
	vec3(-0.7071f, -0.7071f, 0.0f),
	vec3(0.7071f, 0.0f, 0.7071f),
	vec3(-0.7071f, 0.0f, 0.7071f),
	vec3(0.7071f, 0.0f, -0.7071f),
	vec3(-0.7071f, 0.0f, -0.7071f),
	vec3(0.0f, 0.7071f, 0.7071f),
	vec3(0.0f, -0.7071f, 0.7071f),
	vec3(0.0f, 0.7071f, -0.7071f),
	vec3(0.0f, -0.7071f, -0.7071f),
	vec3(0.7071f, 0.7071f, 0.0f),
	vec3(-0.7071f, 0.7071f, 0.0f),
	vec3(0.0f, -0.7071f, 0.7071f),
	vec3(0.0f, -0.7071f, -0.7071f)
};

// NOTE(georgy): Must pe a power of 2!
static uint32_t PermutationTable[512] =
{
	151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
	8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
	35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
	134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
	55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
	18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
	250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
	189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,
	172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
	228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
	107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
};

// TODO(georgy): Make these work with doubles, not float??
// NOTE(georgy): Returns value in [0, 1]
static float
PerlinNoise2D(vec2 P)
{
	int32_t I = FloorReal32ToInt32(P.x);
	int32_t J = FloorReal32ToInt32(P.y);

	uint32_t PermutationForI = PermutationTable[I & (ArrayCount(PermutationTable) - 1)];
	uint32_t PermutationForI1 = PermutationTable[(I + 1) & (ArrayCount(PermutationTable) - 1)];

	vec2 Gradient00 = Gradients2D[PermutationTable[(PermutationForI + J) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients2D) - 1)];
	vec2 Gradient10 = Gradients2D[PermutationTable[(PermutationForI1 + J) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients2D) - 1)];
	vec2 Gradient01 = Gradients2D[PermutationTable[(PermutationForI + J + 1) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients2D) - 1)];
	vec2 Gradient11 = Gradients2D[PermutationTable[(PermutationForI1 + J + 1) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients2D) - 1)];

	float U = P.x - I;
	float V = P.y - J;

	float GradientRamp00 = Dot(Gradient00, vec2(U, V));
	float GradientRamp10 = Dot(Gradient10, vec2(U - 1.0f, V));
	float GradientRamp01 = Dot(Gradient01, vec2(U, V - 1.0f));
	float GradientRamp11 = Dot(Gradient11, vec2(U - 1.0f, V - 1.0f));

	float QuinticFactorForU = U * U * U * (U * (6.0f * U - 15.0f) + 10.0f);
	float QuinticFactorForV = V * V * V * (V * (6.0f * V - 15.0f) + 10.0f);
	float InterpolatedX0 = GradientRamp00 * (1.0f - QuinticFactorForU) + GradientRamp10 * QuinticFactorForU;
	float InterpolatedX1 = GradientRamp01 * (1.0f - QuinticFactorForU) + GradientRamp11 * QuinticFactorForU;
	float Result = InterpolatedX0 * (1.0f - QuinticFactorForV) + InterpolatedX1 * QuinticFactorForV;

	Result = (Result + 0.7071f) * 0.70711356243812756328666383821242f;

	return(Result);
}

// NOTE(georgy): Returns value in [0, 1]
static float
PerlinNoise3D(vec3 P)
{
	int32_t I = FloorReal32ToInt32(P.x);
	int32_t J = FloorReal32ToInt32(P.y);
	int32_t K = FloorReal32ToInt32(P.z);

	uint32_t PermutationForI = PermutationTable[I & (ArrayCount(PermutationTable) - 1)];
	uint32_t PermutationForI1 = PermutationTable[(I + 1) & (ArrayCount(PermutationTable) - 1)];
	uint32_t PermutationForJI = PermutationTable[(J + PermutationForI) & (ArrayCount(PermutationTable) - 1)];
	uint32_t PermutationForJ1I = PermutationTable[((J + 1) + PermutationForI) & (ArrayCount(PermutationTable) - 1)];
	uint32_t PermutationForJI1 = PermutationTable[(J + PermutationForI1) & (ArrayCount(PermutationTable) - 1)];
	uint32_t PermulationForJ1I1 = PermutationTable[((J + 1) + PermutationForI1) & (ArrayCount(PermutationTable) - 1)];

	uint32_t Gradient000Index = PermutationTable[(K + PermutationForJI) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient000 = Gradients3D[Gradient000Index];

	uint32_t Gradient100Index = PermutationTable[(K + PermutationForJI1) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient100 = Gradients3D[Gradient100Index];

	uint32_t Gradient010Index = PermutationTable[(K + PermutationForJ1I) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient010 = Gradients3D[Gradient010Index];

	uint32_t Gradient110Index = PermutationTable[(K + PermulationForJ1I1) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient110 = Gradients3D[Gradient110Index];

	uint32_t Gradient001Index = PermutationTable[((K + 1) + PermutationForJI) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient001 = Gradients3D[Gradient001Index];

	uint32_t Gradient101Index = PermutationTable[((K + 1) + PermutationForJI1) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient101 = Gradients3D[Gradient101Index];

	uint32_t Gradient011Index = PermutationTable[((K + 1) + PermutationForJ1I) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient011 = Gradients3D[Gradient011Index];

	uint32_t Gradient111Index = PermutationTable[((K + 1) + PermulationForJ1I1) & (ArrayCount(PermutationTable) - 1)] &
		(ArrayCount(Gradients3D) - 1);
	vec3 Gradient111 = Gradients3D[Gradient111Index];

	float U = P.x - I;
	float V = P.y - J;
	float T = P.z - K;

	float GradientRamp000 = Dot(Gradient000, vec3(U, V, T));
	float GradientRamp100 = Dot(Gradient100, vec3(U - 1.0f, V, T));
	float GradientRamp010 = Dot(Gradient010, vec3(U, V - 1.0f, T));
	float GradientRamp110 = Dot(Gradient110, vec3(U - 1.0f, V - 1.0f, T));
	float GradientRamp001 = Dot(Gradient001, vec3(U, V, 1.0f - T));
	float GradientRamp101 = Dot(Gradient101, vec3(U - 1.0f, V, 1.0f - T));
	float GradientRamp011 = Dot(Gradient011, vec3(U, V - 1.0f, 1.0f - T));
	float GradientRamp111 = Dot(Gradient111, vec3(U - 1.0f, V - 1.0f, 1.0f - T));

	float QuinticFactorForU = U * U * U * (U * (6.0f * U - 15.0f) + 10.0f);
	float QuinticFactorForV = V * V * V * (V * (6.0f * V - 15.0f) + 10.0f);
	float QuinticFactorForT = T * T * T * (T * (6.0f * T - 15.0f) + 10.0f);
	float InterpolatedX00 = GradientRamp000 * (1.0f - QuinticFactorForU) + GradientRamp100 * QuinticFactorForU;
	float InterpolatedX10 = GradientRamp010 * (1.0f - QuinticFactorForU) + GradientRamp110 * QuinticFactorForU;
	float InterpolatedY0 = InterpolatedX00 * (1.0f - QuinticFactorForV) + InterpolatedX10 * QuinticFactorForV;

	float InterpolatedX01 = GradientRamp001 * (1.0f - QuinticFactorForU) + GradientRamp101 * QuinticFactorForU;
	float InterpolatedX11 = GradientRamp011 * (1.0f - QuinticFactorForU) + GradientRamp111 * QuinticFactorForU;
	float InterpolatedY1 = InterpolatedX01 * (1.0f - QuinticFactorForV) + InterpolatedX11 * QuinticFactorForV;

	float Result = InterpolatedY0 * (1.0f - QuinticFactorForT) + InterpolatedY1 * QuinticFactorForT;

	Result = (Result + 0.7071f) * 0.70711356243812756328666383821242f;

	return(Result);
}

// NOTE(georgy): This simplex noise implementation is taken from SeedWorld engine repository
// 				 https://github.com/ccajas/SeedWorld/blob/master/SeedWorld/Engine/Helpers/Noise/Simplex.cs
static float
Grad(int Hash, float X, float Y)
{
	int H = Hash & 7;      // Convert low 3 bits of hash code
	float U = (H < 4) ? X : Y;  // into 8 simple gradient directions,
	float V = (H < 4) ? Y : X;  // and compute the dot product with (x,y).
	return (((H & 1) != 0) ? -U : U) + (((H & 2) != 0) ? -2.0f * V : 2.0f * V);
}
// NOTE(georgy): Returns value in [-1, 1]
static float
SimplexNoise2D(float x, float y)
{
	const float F2 = 0.366025403f; // F2 = 0.5*(sqrt(3.0)-1.0)
	const float G2 = 0.211324865f; // G2 = (3.0-Math.sqrt(3.0))/6.0

	float n0, n1, n2; // Noise contributions from the three corners

	// Skew the input space to determine which simplex cell we're in
	float s = (x + y) * F2; // Hairy factor for 2D
	float xs = x + s;
	float ys = y + s;
	int i = FloorReal32ToInt32(xs);
	int j = FloorReal32ToInt32(ys);

	float t = (float)(i + j) * G2;
	float X0 = i - t; // Unskew the cell origin back to (x,y) space
	float Y0 = j - t;
	float x0 = x - X0; // The x,y distances from the cell origin
	float y0 = y - Y0;

	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
	if (x0 > y0) { i1 = 1; j1 = 0; } // lower triangle, XY order: (0,0)->(1,0)->(1,1)
	else { i1 = 0; j1 = 1; }      // upper triangle, YX order: (0,0)->(0,1)->(1,1)

	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6

	float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
	float y1 = y0 - j1 + G2;
	float x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
	float y2 = y0 - 1.0f + 2.0f * G2;

	// Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
	int ii = Absolute(i % 256);
	int jj = Absolute(j % 256);

	// Calculate the contribution from the three corners
	float t0 = 0.5f - x0 * x0 - y0 * y0;
	if (t0 < 0.0f) n0 = 0.0f;
	else {
		t0 *= t0;
		n0 = t0 * t0 * Grad(PermutationTable[ii + PermutationTable[jj]], x0, y0);
	}

	float t1 = 0.5f - x1 * x1 - y1 * y1;
	if (t1 < 0.0f) n1 = 0.0f;
	else {
		t1 *= t1;
		n1 = t1 * t1 * Grad(PermutationTable[ii + i1 + PermutationTable[jj + j1]], x1, y1);
	}

	float t2 = 0.5f - x2 * x2 - y2 * y2;
	if (t2 < 0.0f) n2 = 0.0f;
	else {
		t2 *= t2;
		n2 = t2 * t2 * Grad(PermutationTable[ii + 1 + PermutationTable[jj + 1]], x2, y2);
	}

	// Add contributions from each corner to get the final noise value.
	// The result is scaled to return values in the interval [-1,1].
	return 40.0f * (n0 + n1 + n2);
}