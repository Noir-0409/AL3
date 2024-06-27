#include "GameScene.h"
#include "Vector3.h"
#include <vector>

class MapChipField {
public:
	void LoadMapChipCsv(const std::string& filePath);

	uint32_t GetNumBlockVirtical();

	uint32_t GetNumBlockHorizontal();

	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

private:
	MapChipData mapChipData_;

	void ResetMapChipData();
};

enum class MapChipType {

	kBlank, // 空白
	kBlock, // ブロック

};

struct MapChipData {

	std::vector<std::vector<MapChipType>> data;
};