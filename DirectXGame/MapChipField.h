#include <vector>

class MapChipField {

	public:

	// 1�u���b�N�̃T�C�Y
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	// �u���b�N�̌�
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	private:

};

enum class MapChipType {

	kBlank, // ��
	kBlock, // �u���b�N

};

struct MapChipData {

	std::vector<std::vector<MapChipType>> data;

};