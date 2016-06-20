using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace GC
{
    public partial class CPlayer : UnityUtility.CSingleton<CPlayer>
    {
        public void Init()
        {
            UnityGMClient.CClientCore.Singleton.RegisterInitRoleDataCallBack(CbInitRoleData);
            UnityGMClient.CClientCore.Singleton.RegisterUpdateRoleBattleAttributeCallBack(CbUpdateRoleBattleAttribute);
            UnityGMClient.CClientCore.Singleton.RegisterUpdateUInt32AttributeCallBack(CbUpdateUInt32Attribute);
            UnityGMClient.CClientCore.Singleton.RegisterUpdateUInt64AttributeCallBack(CbUpdateUInt64Attribute);
            UnityGMClient.CClientCore.Singleton.RegisterUpdateRoleEquipDataCallBack(CbUpdateRoleEquipData);

            UnityGMClient.CClientCore.Singleton.RegisterNtfInitBagDataCallBack(CbInitBagData);
            UnityGMClient.CClientCore.Singleton.RegisterUpdateBagItemDataCallBack(CbUpdateBagItemData);
            UnityGMClient.CClientCore.Singleton.RegisterUpdateBagSizeCallBack(CbUpdateBagSize);

            UnityGMClient.CClientCore.Singleton.RegisterActiveHotSpringTaskCallBack(CbActiveHotSpringTask);
            
            //UnityGMClient.CClientCore.Singleton.RegisterUpgradePetCallBack(CbUpgradePet);
            UnityGMClient.CClientCore.Singleton.RegisterInitRoleSkillDataCallBack(CbRoleSkillData);

            UnityGMClient.CClientCore.Singleton.RegisterInitChatInfoCallBack(CbRoleChatData);
            UnityGMClient.CClientCore.Singleton.RegisterUpdatePlayerVipScoreCallBack(CbUpdatePlayerVipScore);
            UnityGMClient.CClientCore.Singleton.RegisterRoleAchieveFinishedCallBack(CbAchieveFinished);

            //UnityGMClient.CClientCore.Singleton.RegisterMailSystemGM2GCPushMail(cbRoleMailData);
            UnityGMClient.CClientCore.Singleton.RegisterMsgTaskSystemGM2GCNtfMainTaskCallBack(cbMsgGM2GCNtfMainTaskState);
         }

        private void Log(string content)
        {
            string lg = "[CPlayer]" + content + "";
            GC.CLog.write(lg);
        }
        private void CbInitRoleData(UnityGMClient.EInitRoleDataResult retCode, UInt32 CurrentRoleIndex, UInt32 SceneTypeID, UnityGMClient.CRole a_role)
        {
            string lg = "[CbSelectRole][retCode=" + retCode
                + "][CurrentRoleIndex=" + CurrentRoleIndex
                + "][SceneTypeID=" + SceneTypeID
                + "][level=" + a_role.getLevel()
                + "]\r\n";
            Log(lg);

            if (retCode != UnityGMClient.EInitRoleDataResult.EINITROLEDATA_RESUlT_SUCCESS)
            {
                return;
            }
            GC.CPlayer.Singleton.FinishInitRoleData(CurrentRoleIndex, SceneTypeID, a_role);
        }

        private void CbInitRoleEquipData(UnityGMClient.EGetEquipItemResult retCode, UnityGMClient.CEquipData equipData)
        {
            string lg = "[CbInitRoleEquipData][retCode=" + retCode.ToString() + "][EquipCount=" + equipData.EquipCount + "]\r\n";
            Log(lg);
            if (retCode != UnityGMClient.EGetEquipItemResult.EGETEQUIPITEM_RESUlT_SUCCESS)
            {
                lg = "[CbInitRoleEquipData][retCode=" + retCode.ToString() + "]\r\n";
                Log(lg);
                return;
            }
            setEquip(equipData);
        }

        public void CbInitBagData(UnityGMClient.CBagData bagData)
        {
            string lg = "[CbInitBagData][bagData.BagSize=" + bagData.BagSize + "]\r\n";
            Log(lg);
            setBagData(bagData);
        }

        public void CbGetBagData(UnityGMClient.EGetBagDataResult retCode, UnityGMClient.CBagData bagData)
        {
            string lg = "[CbInitBagData][retCode=" + retCode.ToString() + "][bagData.BagSize=" + bagData.BagSize + "]\r\n";
            Log(lg);
            if (retCode != UnityGMClient.EGetBagDataResult.EINITPACKAGEDATA_RESUlT_SUCCESS)
            {
                lg = "[CbInitBagData][retCode=" + retCode.ToString() + "]\r\n";
                Log(lg);
                return;
            }

            setBagData(bagData);
        }

        private void CbActiveHotSpringTask(UInt32 petID, UnityGMClient.EHotSpringTaskStatus hotSpringTaskStatus, UnityGMClient.EHotSpringTaskType hotSpringTaskType)
        {
            string msg = "触发伙伴ID:" + petID + "type:"+ hotSpringTaskType.ToString();
            GC.CHelper.showMsg("伙伴任务触发", msg);
            SimulateClient.FormPet.showBtnGetPetTaskList(true);
        }

        private void CbUpgradePet(UnityGMClient.CPetItem petItem)
        {
            string lg = "[CbUpgradePet]\r\n" + petItem.getLogString();
            Log(lg);
        }

        private void CbRoleSkillData(List<UnityGMClient.CSkill> listSkill, UInt32[] skillButtons)
        {
            string lg = "[CbRoleSkillData]\r\n";
            Log(lg);
        }

        private void CbRoleChatData(List<UnityGMClient.CChatContent> listWorldContent, List<UnityGMClient.CChatContent> listAnnounceContent)
        {
            string lg = "[CbRoleChatData]\r\n";
            Log(lg);
        }

        private void CbUpdateBagItemData(UnityGMClient.EUpdateBagItemDataResult retCode, UnityGMClient.CItem a_Item)
        {
            string lg = "[CbUpdateBagItemData][retCode=" + retCode.ToString() + "\r\n";
            if (a_Item != null)
            {
                lg += a_Item.getLogString();
            }
            Log(lg);
            if (retCode != UnityGMClient.EUpdateBagItemDataResult.EUPDATEPACKAGEDATA_RESUlT_SUCCESS)
            {
                lg = "[CbUpdateBagItemData][retCode=" + retCode.ToString() + "\r\n";
                Log(lg);
                return;
            }
            updateBagData(a_Item);
        }

        private void CbUpdateBagSize(UInt32 a_bagSize)
        {
            string lg = "[CbUpdateBagSize][a_bagSize=" + a_bagSize.ToString() + "\r\n";
            Log(lg);
            m_roleBagSize = a_bagSize;
        }

        private void CbUpdatePlayerVipScore(UInt32 a_vipScore)
        {
            string lg = "[CbUpdatePlayerVipScore][a_vipScore=" + a_vipScore.ToString() + "\r\n";
            Log(lg);
            m_vipScore = a_vipScore;
        }

        private void CbUpdateRoleEquipData(UnityGMClient.EUpdateRoleEquipDataResult retCode, UnityGMClient.CEquipItem equipItem)
        {
            string lg = "[CbUpdateRoleEquipData][retCode=" + retCode.ToString() + "][EquipID=" + equipItem.EquipID + "][角色装备更新]\r\n";
            Log(lg);
            if (retCode != UnityGMClient.EUpdateRoleEquipDataResult.EUPDATEEQUIPEDATA_RESUlT_SUCCESS)
            {
                lg = "[CbUpdateRoleEquipData]\r\n";
                Log(lg);
                return;
            }
            updateEquip(equipItem);
        }


        private void CbUpdateRoleBattleAttribute(UnityGMClient.CBattleAttribute a_battleAttr,UInt32 a_combat, UInt32 historyMaxCombat)
        {
            string lg = "[CbUpdateRoleBattleAttribute]"+ a_battleAttr.getLogString();
            Log(lg);
            UnityGMClient.CRole role = getCurRole();
            role.setBattleAttr(a_battleAttr);
            role.setCombat(a_combat);
            role.setHistoryMaxCombatPower(historyMaxCombat);
        }

        private void CbUpdateUInt64Attribute(UnityGMClient.EUpdateAttributeResult a_retCode, UInt32 a_attrIndex, UInt64 a_value)
        {
            string lg = "[CbUpdateUInt64Attribute][retCode=" + a_retCode.ToString() + "][a_attrIndex=" + a_attrIndex + "][a_value=" + a_value + "]\r\n";
            Log(lg);
            if (a_retCode != UnityGMClient.EUpdateAttributeResult.EUPDATEATTRIBUTE_RESUlT_SUCCESS)
            {
                return;
            }
            UnityGMClient.CRole role = getCurRole();
            role.updateUInt64Value((UnityGMClient.ERoleAttributeIndex)a_attrIndex, a_value);
        }

        private void CbUpdateUInt32Attribute(UnityGMClient.EUpdateAttributeResult a_retCode, UInt32 a_attributeIndex, UInt32 a_value)
        {
            string lg = "[CbUpdateUInt32Attribute][retCode=" + a_retCode.ToString() 
                + "][a_attributeIndex=" + a_attributeIndex 
                + "][a_value=" + a_value 
                + "]\r\n";
            Log(lg);
            if (a_retCode != UnityGMClient.EUpdateAttributeResult.EUPDATEATTRIBUTE_RESUlT_SUCCESS)
            {
                return;
            }

            UnityGMClient.CRole role = getCurRole();
            role.updateUInt32Value((UnityGMClient.ERoleAttributeIndex)a_attributeIndex, a_value);
            uint power = role.getLightPower();
        }

        private void cbRoleMailData(UInt32 type, List<UnityGMClient.CMail> mailBox)
        {
            string lg = "[cbRoleMailData][type=" + type + "]\r\n";
            Log(lg);

            mailBox.ToArray();
        }

        void cbMsgGM2GCNtfMainTaskState(UInt32 mainTaskTPID, UnityGMClient.ETaskState state, UInt32 curCount)
        {
            GC.CLog.write("cbMsgGM2GCNtfMainTaskState");
        }

        public void InitPlayerData(UnityGMClient.CPlayerData playerData)
        {
            m_roleBaseInfoList.Clear();
            m_vipScore = playerData.VipScore;
            List<UnityGMClient.CRoleBaseInfo> list = playerData.RoleList;
            foreach (UnityGMClient.CRoleBaseInfo role in list)
            {
                UnityGMClient.CRoleBaseInfo roleInfo = new UnityGMClient.CRoleBaseInfo();
                roleInfo = role;
                UInt32 key = roleInfo.getRoleIndex();
                m_roleBaseInfoList.Add(key, roleInfo);
            }
        }

        public void AddRoleBaseInfo(UnityGMClient.CRoleBaseInfo role)
        {
            if (m_roleBaseInfoList == null)
            {
                m_roleBaseInfoList = new Hashtable();
            }
            m_roleBaseInfoList.Add(role.getRoleIndex(), role);
        }

        public bool RemoveRole(UInt32 a_curRoleIndex)
        {
            if (!m_roleBaseInfoList.ContainsKey(a_curRoleIndex))
            {
                return false;
            }

            m_roleBaseInfoList.Remove(a_curRoleIndex);
            return true;
        }

        public void FinishCreateRole(UInt32 a_curRoleIndex, UnityGMClient.CRole a_role)
        {
            if (m_roleBaseInfoList.ContainsKey(a_curRoleIndex))
            {
                return;
            }

            UnityGMClient.CRoleBaseInfo roleInfo = new UnityGMClient.CRoleBaseInfo();
            roleInfo.setRoleIndex(a_curRoleIndex);
            roleInfo.setRoleLevel(a_role.getLevel());
            roleInfo.setRoleName(a_role.getRoleName());
            roleInfo.setRoleTPID(a_role.getRoleTPID());
            m_curRole = a_role;
            AddRoleBaseInfo(roleInfo);
            string lg = "[FinishCreateRole]" + a_role.getLogString();
            Log(lg);
        }

        public void FinishInitRoleData(UInt32 a_curRoleIndex, UInt32 a_sceneTypeID, UnityGMClient.CRole a_role)
        {
            UnityUtility.CTrace.Singleton.debug("FinishInitRoleData[curRoleIndex={0}][a_sceneTypeID={1}][roleIndex ={2}]", a_curRoleIndex, a_sceneTypeID, a_role.getRoleIndex());
            m_sceneTypeID = a_sceneTypeID;
            UnityGMClient.CRole role = getCurRole();
            m_curRole = a_role;
            string lg = "[FinishInitRoleData]" + role.getLogString();
            Log(lg);
        }

        public void FinishEnterScene(UInt32 a_sceneID)
        {
            m_currentSceneID = a_sceneID;
        }

        public void FinishUpdateAttribute(UInt32 retCode)
        {
        }

        public void setCurrentSceneID(UInt32 a_currentSceneID)
        {
            m_currentSceneID = a_currentSceneID;
        }

        public Hashtable getRoleBaseInfoList() 
        {
            return m_roleBaseInfoList; 
        }

        public Int32 getRoleCount()
        {
            if (m_roleBaseInfoList == null)
            {
                return -1;
            }
            return m_roleBaseInfoList.Count; 
        }

        public UInt32 getSceneTypeID()
        {
            return m_sceneTypeID; 
        }

        public UInt64 getCurrentSceneID()
        {
            return m_currentSceneID;
        }

        public UnityGMClient.CRole getCurRole()
        {
            return m_curRole;
        }
        public Int32 getCurrentRoleIndex()
        {
            if (null == m_curRole)
            {
                return -1;
            }
            else
            {
                return (Int32)m_curRole.getRoleIndex();
            }
        }

        public UInt32 getVipScore()
        {
            return m_vipScore;
        }

        public bool setEquip(UnityGMClient.CEquipData a_equipData)
        {
            m_equipData = a_equipData;
            return true;
        }

        public bool updateEquip(UnityGMClient.CEquipItem a_equipItem)
        {
            for (int i = 0; i < m_equipData.EquipCount; ++i)
            {
                if (a_equipItem.EquipID != m_equipData.EquipList[i].EquipID)
                {
                    continue;
                }

                m_equipData.EquipList[i].EquipID = a_equipItem.EquipID;
                m_equipData.EquipList[i].EquipLevel = a_equipItem.EquipLevel;
                m_equipData.EquipList[i].EquipTPID = a_equipItem.EquipTPID;
                m_equipData.EquipList[i].EquipType = a_equipItem.EquipType;
                for (int j = 0; j < 4; ++j)
                {
                    m_equipData.EquipList[i].updateGem(a_equipItem.GemList);
                }
            }

            return true;
        }

        public bool setBagData(UnityGMClient.CBagData a_bagData)
        {
            m_bagData = a_bagData; 
            return true;
        }

        public bool updateBagData(UnityGMClient.CItem a_item)
        {
            m_bagData.UpdateBagItem(a_item);
            return true;
        }

        public bool setPetData(UnityGMClient.CPetData a_data)
        {
            m_petData = a_data;
            return true;
        }

        public void updatePetStatus(UInt32 PetID,UnityGMClient.EPetStatus status)
        {
            UnityGMClient.CPetItem oldPetItem = m_petData.getPetItem(PetID);
            if (oldPetItem == null)
            {
                return;
            }
            oldPetItem.PetStatus = status;
        }

        public string getPlayerDataToLogString()
        {
            UnityGMClient.SAccountKey key = UnityGMClient.CClientCore.Singleton.getAccountKey();
            string data = string.Format("[m_accountID={0},m_zoneID={1},roleCount={2},VipScore={3}]\r\n", key.m_accountID, key.m_zoneID, m_roleBaseInfoList.Count, m_vipScore);
            foreach (DictionaryEntry roleData in m_roleBaseInfoList)
            {
                UnityGMClient.CRoleBaseInfo role = (UnityGMClient.CRoleBaseInfo)roleData.Value;
                data += string.Format("[roleIndex={0}][name={1}][tpid={2}][level={3}]\r\n", role.getRoleIndex(), role.getRoleName(), role.getRoleTPID(), role.getLevel());
            }
            return data;
        }

        public string getRoleDataToLogString()
        {
            string lg = "";
            UnityGMClient.CRole role = GC.CPlayer.Singleton.getCurRole();
            if (role != null)
            {
                lg = role.getLogString();
            }
            return lg;
        }

        public string getEquipDataToLogString()
        {
            string lg = "";
            UnityGMClient.CRole role = GC.CPlayer.Singleton.getCurRole();
            if (role != null)
            {
                lg = "[roleName=" + role.getRoleName() + "]" + "[roleType:" + role.getRoleTPID() + "]" + "\r\n";
                lg += GC.CPlayer.Singleton.m_equipData.getLogString();
            }
            return lg;
        }

        public string getBagDataToLogString()
        {
            return GC.CPlayer.Singleton.m_bagData.getLogString();
        }

        public bool getPetDataFromServer()
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqInitPetData(
               delegate(UnityGMClient.EGetInitRolePetDataResult retCode, UnityGMClient.CPetData petData)
               {
                   string lg = "EGetInitRolePetDataResult:" + retCode.ToString();
                   Log(lg);
                   GC.CPlayer.Singleton.setPetData(petData);
                   
               });
            return bResult;
        }

        public string getPetDataToLogString()
        {
            string lg = "";
            lg += "\r\n" + GC.CPlayer.Singleton.m_petData.getLogString() + "\r\n";
            return lg;
        }

        private void CbDeleteRole(UnityGMClient.EDeleteRoleResult retCode, UInt32 roleIndex)
        {
            if (m_roleBaseInfoList.ContainsKey(roleIndex))
            {
                m_roleBaseInfoList.Remove(roleIndex);
            }
        }

        private void CbAchieveFinished(UInt32 a_achieveID)
        {
            string lg = "[NTF][AchieveFinished][achieveID=" + a_achieveID + "]";
            Log(lg);
        }

        private Hashtable getBaseInfoList()
        {
            return m_roleBaseInfoList;
        }

        public UInt32 BagSize
        {
            set{ m_roleBagSize = value;}
            get{ return m_roleBagSize;}
        }

        public UnityGMClient.EHotSpringTaskType CurHotSpringTaskType
        {
            get { return m_curHotSpringTaskType; }
            set { m_curHotSpringTaskType = value; }
        }

        private UInt32 m_sceneTypeID = 0;
        private UInt32 m_currentSceneID = 0;
        private UInt32 m_vipScore = 0;

        private UInt32 m_roleBagSize = 0;
        UnityGMClient.CRole m_curRole = new UnityGMClient.CRole();
        private Hashtable m_roleBaseInfoList = new Hashtable();
       
        public UnityGMClient.CBagData m_bagData = new UnityGMClient.CBagData();
        public UnityGMClient.CPetData m_petData = new UnityGMClient.CPetData();
        public UnityGMClient.CEquipData m_equipData = new UnityGMClient.CEquipData();
        public UnityGMClient.CHotSpring m_hotSpring = new UnityGMClient.CHotSpring();

        public string m_taken = "";
        public UInt64 m_accountID = 0;
        public string m_account = "";
        UnityGMClient.EHotSpringTaskType m_curHotSpringTaskType = UnityGMClient.EHotSpringTaskType.EHotSpringTaskTypeInvalid;

        
    }
}
