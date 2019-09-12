// Reemplazar
	if (!pEventSet->ScriptGroup.Create(strEventString))
	{
		__ClearEventSetp(pEventSet);
		return -1;
	}

// Por
	int iScriptGroup = pEventSet->ScriptGroup.Create(strEventString);
	if (-1 == iScriptGroup)
	{
		__ClearEventSetp(pEventSet);
		return -1;
	}

	pEventSet->iTotalLineCount = iScriptGroup;

// Reemplazar
	if (!pEventSet->ScriptGroup.Create(strScript))
	{
		__ClearEventSetp(pEventSet);
		return -1;
	}
// Por
	int iScriptGroup = pEventSet->ScriptGroup.Create(strScript);
	if (-1 == iScriptGroup)
	{
		__ClearEventSetp(pEventSet);
		return -1;
	}

	pEventSet->iTotalLineCount = iScriptGroup;

// Arriba de
void CPythonEventManager::ClearLine(TEventSet * pEventSet)
{
	...
	...
}

// Agregar
int CPythonEventManager::GetTotalLineCount(int iIndex)
{
	if (!CheckEventSetIndex(iIndex))
		return 0;

	TEventSet * pEventSet = m_EventSetVector[iIndex];
	if (!pEventSet)
		return 0;

	return pEventSet->iTotalLineCount;
}