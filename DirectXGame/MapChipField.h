#include <vector>
#include "Vector3.h"

class MapChipField {

	public:

	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	auto GetNumBlockVirical() { return kNumBlockVirtical; }
	auto GetNumBlockHorizontal() {return kNumBlockHorizontal;}

	private:

};

enum class MapChipType {

	kBlank, // 空白
	kBlock, // ブロック

};

struct MapChipData {

	std::vector<std::vector<MapChipType>> data;

};