#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
namespace ApplezEng
{

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		// setters
		void setPosition(const glm::vec3& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

		// getters
		glm::vec3 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		int _screenWidth;
		int _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec3 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};
}