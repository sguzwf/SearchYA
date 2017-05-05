#include "Document.h"
#include "Communication/Serializor.h"

using namespace std;

Document::Document(const string& name, vector<pair<string, int>>& words)
	:m_name(name)
{
	for(auto& vecPair : words)
	{
		m_words[vecPair.first] = vecPair.second;
	}
}


Document::Document(const Document&& obj)
{
	string tempName(move(obj.GetName()));
	unordered_map<string, int> tempWords(move(obj.GetWords()));
	m_name = move(tempName);
	m_words = move(tempWords);
}

Document& Document::operator=(const Document&& obj)
{
	string tempName(move(obj.GetName()));
	unordered_map<string, int> tempWords(move(obj.GetWords()));
	m_name = move(tempName);
	m_words = move(tempWords);
	return *this;
}

string Document::Serialize(Document& document)
{
	Serializor serializeContext;
	Serializor::Serialize(serializeContext, document.GetName());
	Serializor::Serialize(serializeContext, (int)document.GetWords().size());
	for(auto& hashPair : document.GetWords())
	{
		Serializor::Serialize(serializeContext, hashPair.first);	
		Serializor::Serialize(serializeContext, hashPair.second);	
	}
	return serializeContext.GetBuffer();
}

Document Document::Deserialize(const char *data, int length)
{
	Serializor serializeContext(data, length);
	string name = Serializor::DeserializeString(serializeContext);
	int wordsCount = Serializor::DeserializeInt(serializeContext);
	vector<pair<string, int>> words;
	words.reserve(wordsCount);
	for(int index = 0; index < wordsCount; index++)
	{
		words.emplace_back(Serializor::DeserializeString(serializeContext), 
				Serializor::DeserializeInt(serializeContext));
	}
	return Document(name, words);
}