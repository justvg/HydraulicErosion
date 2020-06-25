#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define Assert(Expression) if(!(Expression)) { *(int *)0 = 0; }
#define ArrayCount(Array) (sizeof(Array)/sizeof((Array)[0]))

#include "math_utils.cpp"
#include "shader.h"
#include <vector>

static void
WaterErosion(float *HeightMap, uint32_t GridWidth, uint32_t GridHeight)
{
	const uint32_t DropletsCount = 75000;
	const uint32_t MaxLifeTime = 30;

	srand(1337);
	for(uint32_t Droplet = 0; Droplet < DropletsCount; Droplet++)
	{
		// NOTE(georgy): Get random position for droplet
		float X = rand() % GridWidth;
		float Z = rand() % GridHeight;
		vec2 DropletP = vec2(X, Z);
		vec2 DropletDir = vec2(0.0f, 0.0f);
		float DropletSediment = 0.0f;
		float DropletSpeed = 1.0f;
		float DropletWater = 1.0f;

		float DropletInertia = 0.4f;
		float DropletCapacityFactor = 2.0f;
		float MinCarryCapacity = 0.001f;
		float DropletDeposition = 0.1f;
		float DropletErosion = 0.3f;
		float DropletEvaporation = 0.1f;
		float Gravity = 4.0f;
		int32_t Radius = 6;

		for(uint32_t LifeTime = 0; LifeTime < MaxLifeTime; LifeTime++)
		{
			// NOTE(georgy): Current droplet's grid cell indices
			uint32_t XIndex = (uint32_t)DropletP.x;
			uint32_t ZIndex = (uint32_t)DropletP.y;
			uint32_t Grid00Index = XIndex + ZIndex*(GridWidth + 1);
			uint32_t Grid01Index = Grid00Index + 1;
			uint32_t Grid10Index = Grid00Index + (GridWidth + 1);
			uint32_t Grid11Index = Grid00Index + (GridWidth + 1) + 1;

			// NOTE(georgy): Droplet's offset inside the cell
			float U = (DropletP.x - XIndex);
			float V = (DropletP.y - ZIndex);

			// NOTE(georgy): Find current height, gradient and direction
			float Height00 = HeightMap[Grid00Index];
			float Height01 = HeightMap[Grid01Index];
			float Height10 = HeightMap[Grid10Index];
			float Height11 = HeightMap[Grid11Index];
			vec2 Grad00 = vec2(Height01 - Height00, Height10 - Height00);
			vec2 Grad01 = vec2(Height01 - Height00, Height11 - Height01);
			vec2 Grad10 = vec2(Height11 - Height10, Height10 - Height00);
			vec2 Grad11 = vec2(Height11 - Height10, Height11 - Height01);
			vec2 GradInterpolation0 = Lerp(Grad00, Grad01, U);
			vec2 GradInterpolation1 = Lerp(Grad10, Grad11, U);
			vec2 Grad = Lerp(GradInterpolation0, GradInterpolation1, V);

			vec2 OldP = DropletP;
			DropletDir = NOZ(Lerp(Grad, DropletDir, DropletInertia));
			DropletP -= DropletDir;

			float OldHeightInterpolation0 = Lerp(Height00, Height01, U);
			float OldHeightInterpolation1 = Lerp(Height10, Height11, U);
			float OldHeight = Lerp(OldHeightInterpolation0, OldHeightInterpolation1, V);

			if(((DropletDir.x == 0.0f) && (DropletDir.y == 0.0f)) ||
			    (DropletP.x < 0.0f) || (DropletP.x >= GridWidth) ||
				(DropletP.y < 0.0f) || (DropletP.y >= GridHeight))
			{
				break;	
			}

			// NOTE(georgy): New droplet's position grid cell indices
			uint32_t NewXIndex = (uint32_t)DropletP.x;
			uint32_t NewZIndex = (uint32_t)DropletP.y;
			uint32_t NewGrid00Index = NewXIndex + NewZIndex*(GridWidth + 1);
			uint32_t NewGrid01Index = NewGrid00Index + 1;
			uint32_t NewGrid10Index = NewGrid00Index + (GridWidth + 1);
			uint32_t NewGrid11Index = NewGrid00Index + (GridWidth + 1) + 1;

			// NOTE(georgy): New droplet's offset inside the cell
			float NewU = (DropletP.x - NewXIndex);
			float NewV = (DropletP.y - NewZIndex);

			// NOTE(georgy): Find new height
			float NewHeight00 = HeightMap[NewGrid00Index];
			float NewHeight01 = HeightMap[NewGrid01Index];
			float NewHeight10 = HeightMap[NewGrid10Index];
			float NewHeight11 = HeightMap[NewGrid11Index];
			float NewHeightInterpolation0 = Lerp(NewHeight00, NewHeight01, NewU);
			float NewHeightInterpolation1 = Lerp(NewHeight10, NewHeight11, NewU);
			float NewHeight = Lerp(NewHeightInterpolation0, NewHeightInterpolation1, NewV);

			// NOTE(georgy): Find the difference between old and new heightm, and calculate new carry capacity
			float HeightDiff = NewHeight - OldHeight;
			float DropletCarryCapacity = Max(-HeightDiff*DropletSpeed*DropletWater*DropletCapacityFactor, MinCarryCapacity);

			// NOTE(georgy): If droplet's carrying more than it has capacity, or if NewHeight > OldHeight
			if((DropletCarryCapacity < DropletSediment) || (HeightDiff > 0))
			{
				float DropAmount = (HeightDiff > 0) ? Min(DropletSediment, HeightDiff) : (DropletSediment - DropletCarryCapacity)*DropletDeposition;
				DropletSediment -= DropAmount;

				HeightMap[Grid00Index] += DropAmount*(1.0f - U)*(1.0f - V);
				HeightMap[Grid01Index] += DropAmount*U*(1.0f - V);
				HeightMap[Grid10Index] += DropAmount*(1.0f - U)*V;
				HeightMap[Grid11Index] += DropAmount*U*V;
			}
			else
			{
				// NOTE(georgy): Erosion
				float TakeAmount = Min((DropletCarryCapacity - DropletSediment)*DropletErosion, -HeightDiff);

				float WeightSum = 0.0f;
				for(int32_t ZOffset = -Radius; ZOffset <= Radius; ZOffset++)
				{
					for(int32_t XOffset = -Radius; XOffset <= Radius; XOffset++)
					{
						int32_t XInd = XIndex + XOffset;
						int32_t ZInd = ZIndex + ZOffset;
						if((XInd >= 0) && (XInd <= GridWidth) && (ZInd >= 0) && (ZInd <= GridHeight))
						{
							WeightSum += Max(0.0f, Radius - Length(vec2i(XInd, ZInd) - OldP));
						}
					}
				}

				for(int32_t ZOffset = -Radius; ZOffset <= Radius; ZOffset++)
				{
					for(int32_t XOffset = -Radius; XOffset <= Radius; XOffset++)
					{
						int32_t XInd = XIndex + XOffset;
						int32_t ZInd = ZIndex + ZOffset;
						if((XInd >= 0) && (XInd <= GridWidth) && (ZInd >= 0) && (ZInd <= GridHeight))
						{
							float Weight = Max(0.0f, Radius - Length(vec2i(XInd, ZInd) - OldP)) / WeightSum;
							float AmountToErode = Weight*TakeAmount;
							float DeltaSediment = (HeightMap[XInd + ZInd*(GridWidth+1)] < AmountToErode) ? HeightMap[XInd + ZInd*(GridWidth+1)] : AmountToErode;
							HeightMap[XInd + ZInd*(GridWidth+1)] -= DeltaSediment;
							DropletSediment += DeltaSediment;
						}
					}
				}
			}

			// NOTE(georgy): New speed and water
			// TODO(georgy): I think, not plus but minus HeightDiff*Gravity is more correct. If we flow down, we want our speed to increase??
			DropletSpeed = SquareRoot(Square(DropletSpeed) + HeightDiff*Gravity); 
			DropletWater *= (1.0f - DropletEvaporation);
		}
	}
}

static vec3
CalculateNormal(float *HeightMap, uint32_t GridWidth, uint32_t GridHeight, uint32_t X, uint32_t Z)
{
	if(X == 0) X = 1;
	if(Z == 0) Z = 1;
	if(X == GridWidth) X = GridWidth - 1;
	if(Z == GridHeight) Z = GridHeight - 1;

	float HeightLeft = HeightMap[(X - 1) + Z*(GridWidth + 1)];
	float HeightRight = HeightMap[(X + 1) + Z*(GridWidth + 1)];
	float HeightDown = HeightMap[X + (Z - 1)*(GridWidth + 1)];
	float HeightUp = HeightMap[X + (Z + 1)*(GridWidth + 1)];

	vec3 Normal = Normalize(vec3(HeightLeft - HeightRight, 0.125f, HeightUp - HeightDown));
	return(Normal);
}

static void
GenerateTerrain(std::vector<vec3> &Vertices, std::vector<vec3> &Normals, std::vector<uint32_t> &Indices)
{
	const uint32_t GridWidth = 512;
	const uint32_t GridHeight = 512;

	const float TerrainWidth = 32.0f;
	const float TerrainHeight = 32.0f;
	const float MaxHeight = 10.0f;

	float* HeightMap = (float*)malloc(sizeof(float) * (GridWidth + 1) * (GridHeight + 1));
	if (HeightMap)
	{
		memset(HeightMap, 0, sizeof(float) * (GridWidth + 1) * (GridHeight + 1));
		for(uint32_t Z = 0; Z <= GridHeight; Z++)
		{
			for(uint32_t X = 0; X <= GridWidth; X++)
			{
				float Noise = 1.5f*(0.5f*PerlinNoise2D(vec2(0.5f*0.01345f*X, -0.5f*0.01345f*Z)) + 0.5f);
				Noise += 0.5f*(0.5f*PerlinNoise2D(vec2(1.0f*0.01345f*X, -1.0f*0.01345f*Z)) + 0.5f);
				Noise += 0.25f*(0.5f*PerlinNoise2D(vec2(2.0f*0.01345f*X, -2.0f*0.01345f*Z)) + 0.5f);
				Noise += 0.125f*(0.5f*PerlinNoise2D(vec2(4.0f*0.01345f*X, -4.0f*0.01345f*Z)) + 0.5f);
				float Height = MaxHeight*Noise;
				HeightMap[X + Z*(GridWidth + 1)] = Height;
			}	
		}

		WaterErosion(HeightMap, GridWidth, GridHeight);

		float StepX = TerrainWidth / GridWidth;
		float StepZ = TerrainHeight / GridHeight;
		for(uint32_t Z = 0; Z <= GridHeight; Z++)
		{
			for(uint32_t X = 0; X <= GridWidth; X++)
			{
				float Height = HeightMap[X + Z*(GridWidth + 1)];
				vec3 P = vec3(StepX*X, Height, -StepZ*Z);
				vec3 Normal = CalculateNormal(HeightMap, GridWidth, GridHeight, X, Z);

				Vertices.push_back(P);
				Normals.push_back(Normal);
			}	
		}

		for(uint32_t Z = 0; Z < GridHeight; Z++)
		{
			for(uint32_t X = 0; X <= GridWidth; X++)
			{
				uint32_t Index0 = X + Z*(GridWidth + 1);
				uint32_t Index1 = X + (Z + 1)*(GridWidth + 1);

				Indices.push_back(Index0);
				Indices.push_back(Index1);

				if(X == GridWidth)
				{
					Indices.push_back(Index1);
					Indices.push_back((Z + 1)*(GridWidth + 1));
				}
			}	
		}

		free(HeightMap);
	}
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	GLFWwindow* Window = glfwCreateWindow(900, 540, "WaterErosion", 0, 0);
	glfwMakeContextCurrent(Window);
	glfwSwapInterval(1);

	glewInit();

	glViewport(0, 0, 900, 540);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_FRAMEBUFFER_SRGB);

	GLuint VAO, PosVBO, NormalsVBO, EBO;
	std::vector<vec3> Vertices;
	std::vector<vec3> Normals;
	std::vector<uint32_t> Indices;
	GenerateTerrain(Vertices, Normals, Indices);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &PosVBO);
	glGenBuffers(1, &NormalsVBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, PosVBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size()*sizeof(vec3), &Vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, NormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, Normals.size()*sizeof(vec3), &Normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size()*sizeof(uint32_t), &Indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);

	glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
	shader Shader("shaders\\VS.glsl", "shaders\\FS.glsl");

	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 Projection = Perspective(45.0f, 900.0f / 540.0f, 0.1f, 200.0f);
		mat4 View = LookAt(1.2f*vec3(-2.0f, 30.0f, 5.0f), vec3(8.0f, 22.0f, -5.0f));
		
		Shader.Use();
		Shader.SetMat4("Projection", Projection);
		Shader.SetMat4("View", View);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_STRIP, Indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(Window);
	}

	return(0);
}