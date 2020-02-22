#pragma once


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <map>
#include <array>
#include <vector>

#include <glmCommon.hpp>
#include "../sModelDrawInfo.h"

class cSkinnedMesh
{
public:

	static const int MAX_BONES_PER_VERTEX = 4;
private:
	struct SceneImporter
	{
		const aiScene* Scene;
		Assimp::Importer Importer;
	};
	static std::map<std::string, SceneImporter> FullScenes;
	static std::map<std::string, SceneImporter> AnimationOnly;

	unsigned mMeshIndex;

	struct sVertexBoneData
	{
		//std::array<unsigned int, MAX_BONES_PER_VERTEX> ids;
		std::array<float, MAX_BONES_PER_VERTEX> ids;
		std::array<float, MAX_BONES_PER_VERTEX> weights;

		void AddBoneData(unsigned int BoneID, float Weight);
	};

	struct sBoneInfo
	{
		std::string boneName;
		glm::mat4 BoneOffset;
		glm::mat4 FinalTransformation;
		glm::mat4 ObjectBoneTransformation;
	};

	unsigned int m_numberOfVertices;
	unsigned int m_numberOfIndices;
	unsigned int m_numberOfTriangles;


public:
	bool Initialize();

	cSkinnedMesh(void);
	virtual ~cSkinnedMesh(void);

	bool LoadMeshFromFile(const std::string& friendlyName,
						  const std::string& filename,
						  const unsigned int meshIndex = 0);		// mesh we draw
	bool LoadMeshAnimation(const std::string& friendlyName,
						   const std::string& filename,
						   const unsigned int aniIndex = 0);	// Only want animations


	void LoadBones(const aiMesh* Mesh, std::vector<sVertexBoneData>& Bones);

	sModelDrawInfo* CreateModelDrawInfoObjectFromCurrentModel();

	void BoneTransform(float TimeInSeconds,
					   std::string animationName,		// Now we can pick the animation
					   std::vector<glm::mat4>& FinalTransformation,
					   std::vector<glm::mat4>& Globals,
					   std::vector<glm::mat4>& Offsets);

	void ReadNodeHeirarchy(float AnimationTime,
						   std::string animationName,		// Now with more "choose animation"
						   const aiNode* pNode,
						   const glm::mat4& parentTransformMatrix);

	void CalcInterpolatedRotation(float AnimationTime, const aiNodeAnim* pNodeAnim, aiQuaternion& out);
	void CalcInterpolatedPosition(float AnimationTime, const aiNodeAnim* pNodeAnim, aiVector3D& out);
	void CalcInterpolatedScaling(float AnimationTime, const aiNodeAnim* pNodeAnim, aiVector3D& out);

	void CalcGLMInterpolatedRotation(float AnimationTime, const aiNodeAnim* pNodeAnim, glm::quat& out);
	void CalcGLMInterpolatedPosition(float AnimationTime, const aiNodeAnim* pNodeAnim, glm::vec3& out);
	void CalcGLMInterpolatedScaling(float AnimationTime, const aiNodeAnim* pNodeAnim, glm::vec3& out);

	unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

	const aiNodeAnim* FindNodeAnimationChannel(const aiAnimation* pAnimation, aiString nodeOrBoneName);

	float GetDuration(void);

	std::string fileName;
	std::string friendlyName;

	const aiScene* mScene;

	struct sAnimationInfo
	{
		std::string friendlyName;
		std::string fileName;
		unsigned animationIndex;
		float animationTime;
		const aiScene* pAIScene;
	};

	std::map< std::string /*animation FRIENDLY name*/,
		sAnimationInfo > mapAnimationFriendlyNameTo_pScene;		// Animations

	std::vector<sVertexBoneData> vecVertexBoneData;	//Bones;
	glm::mat4 mGlobalInverseTransformation;

	//	std::vector<sMeshEntry> mMeshEntries;
	std::map<std::string /*BoneName*/, unsigned int /*BoneIndex*/> m_mapBoneNameToBoneIndex;	//mMapping;
	std::vector<sBoneInfo> mBoneInfo;
	unsigned int mNumBones;	//mNums;
};
