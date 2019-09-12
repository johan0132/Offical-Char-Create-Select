// Reemplazar
int Group::Create(const std::string & stSource)
{
	....
	....
}

// Por
int Group::Create(const std::string & stSource)
{
	m_cmdList.clear();

	if (stSource.empty())
		return -1;

	const char * str_base = stSource.c_str();
	if (!str_base || !*str_base)
	{
		TraceError("Source file has no content");
		return -1;
	}
	int str_len = stSource.length();
	int str_pos = 0;
	int len_line = 0;

	uint32_t codePage = GetDefaultCodePage();

	char box_data[1024 + 1];

	static std::string stLetter;

	while (str_pos < str_len)
	{
		TCmd cmd;

		const char * word = str_base + str_pos;
		const char * word_next = CharNextExA(codePage, word, 0);

		int word_len = word_next - word;

		if (word_len > 1)
		{
			str_pos += word_len;

			{
				stLetter.assign(word, word_next);

				cmd.name.assign("LETTER");
				cmd.argList.emplace_back(TArg("value", stLetter));

				m_cmdList.emplace_back(cmd);
			}
		}
		else if (word_len == 1)
		{
			const char cur = *word;

			if ('[' == cur)
			{
				++str_pos;

				const char * box_begin = str_base + str_pos;
				const char * box_end = LocaleString_FindChar(box_begin, str_len - str_pos, ']');
				if (!box_end)
				{
					TraceError(" !! PARSING ERROR - Syntax Error : %s\n", box_begin);
					return -1;
				}
				str_pos += box_end - box_begin + 1;


				int data_len = 0;
				{
					const char * data_begin = LocaleString_Skip(codePage, box_begin);
					const char * data_end = box_end;
					data_len = data_end - data_begin;
					if (data_len >= 1024)
					{
						TraceError(" !! PARSING ERROR - Buffer Overflow : %d, %s\n", data_len, str_base);
						return -1;
					}
					memcpy(box_data, data_begin, data_len);
					box_data[data_len] = '\0';

					data_len = LocaleString_RightTrim(box_data, data_len); // 오른쪽 빈칸 자르기
				}

				{
					const char * space = LocaleString_FindChar(box_data, data_len, ' ');
					if (space)
					{
						int name_len = space - box_data;
						cmd.name.assign(box_data, name_len);

						const char * space_next = CharNextExA(codePage, space, 0);
						const char * arg = LocaleString_Skip(codePage, space_next);

						int arg_len = data_len - (arg - box_data);

						if (!GetArg(arg, arg_len, cmd.argList))
						{
							TraceError(" !! PARSING ERROR - Unknown Arguments : %d, %s\n", arg_len, arg);
							return -1;
						}
					}
					else
					{
						cmd.name.assign(box_data);
						cmd.argList.clear();
					}

					m_cmdList.emplace_back(cmd);
				}
			}
			else if (cur == '\r' || cur == '\n')
			{
				if (cur == '\n') len_line += 1;
				++str_pos;
			}
			else
			{
				++str_pos;

				{
					stLetter.assign(1, cur);
					cmd.name.assign("LETTER");
					cmd.argList.emplace_back(TArg("value", stLetter));
					m_cmdList.emplace_back(cmd);
				}
			}
		}
		else
			break;
	}

	return len_line;
}
