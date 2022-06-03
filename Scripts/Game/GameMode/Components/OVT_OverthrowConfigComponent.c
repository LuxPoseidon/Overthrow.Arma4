class OVT_OverthrowConfigComponentClass: OVT_ComponentClass
{	
};

class OVT_DifficultySettings : Managed
{
	//Wanted system
	int wantedTimeout = 30000;		//Timeout for wanted levels 2-5 (per level)
	int wantedOneTimeout = 120000;	//Timeout for wanted level 1
	
	//OF
	int startingResources = 5000; 	//OF starting resources
	int baseResourcesPerTick = 500;//OF resources per 6 hrs
	int resourcesPerTick = 1000;	//Additional OF resources per 6 hrs (* threat)
	int resourcesPerSoldier = 10;	//Resource cost per soldier
	int initialResourcesPerBase = 300; //Initial starting resources per base;
	
	//RF
	int startingCash = 250;			//Player starting cash
	int baseThreat = 0;				//Base RF threat
}


class OVT_OverthrowConfigComponent: OVT_Component
{
	[Attribute( defvalue: "FIA", uiwidget: UIWidgets.EditBox, desc: "Faction affiliation of the player's side", category: "Factions")]
	string m_sPlayerFaction;
	
	[Attribute( defvalue: "USSR", uiwidget: UIWidgets.EditBox, desc: "The faction occupying this map (the enemy)", category: "Factions")]
	string m_sOccupyingFaction;
	
	[Attribute( defvalue: "US", uiwidget: UIWidgets.EditBox, desc: "The faction supporting the player", category: "Factions")]
	string m_sSupportingFaction;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Base Controller Prefab", params: "et", category: "Controllers")]
	ResourceName m_pBaseControllerPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Players starting car", params: "et", category: "Vehicles")]
	ResourceName m_pStartingCarPrefab;
	
	ref OVT_DifficultySettings m_Difficulty;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Move Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pMoveWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Defend Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pDefendWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Patrol Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pPatrolWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Wait Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pWaitWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Cycle Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pCycleWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Search and Destroy Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pSearchAndDestroyWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Get In Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pGetInWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Smart Action Waypoint Prefab", params: "et", category: "Waypoints")]
	ResourceName m_pSmartActionWaypointPrefab;
	
	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Map Marker Prefab", params: "et")]
	ResourceName m_pMapMarkerPrefab;
	
	[Attribute(defvalue: "4", UIWidgets.EditBox, desc: "Time multiplier")]
	int m_iTimeMultiplier;
	
	// Instance of this component
	private static OVT_OverthrowConfigComponent s_Instance = null;
	
	static OVT_OverthrowConfigComponent GetInstance()
	{
		if (!s_Instance)
		{
			BaseGameMode pGameMode = GetGame().GetGameMode();
			if (pGameMode)
				s_Instance = OVT_OverthrowConfigComponent.Cast(pGameMode.FindComponent(OVT_OverthrowConfigComponent));
		}

		return s_Instance;
	}
	
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		
		OVT_OverthrowGameMode gameMode = OVT_OverthrowGameMode.Cast(owner);
		if (!gameMode)
			// If parent is not gamemode, print an error
			Print("OVT_OverthrowConfigComponent has to be attached to a OVT_OverthrowGameMode (or inherited) entity!", LogLevel.ERROR);
			
		
	}
	
	void SpawnMarkerLocal(vector pos, EMapDescriptorType type, string name = "")
	{
		EntitySpawnParams params = EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform[3] = pos;
		IEntity ent = GetGame().SpawnEntityPrefabLocal(Resource.Load(m_pMapMarkerPrefab), null, params);
		SCR_MapDescriptorComponent mapdesc = SCR_MapDescriptorComponent.Cast(ent.FindComponent(SCR_MapDescriptorComponent));
		mapdesc.Item().SetBaseType(type);
		mapdesc.Item().SetDisplayName(name);
	}
	
	void SpawnMarker(vector pos, EMapDescriptorType type, string name = "")
	{
		EntitySpawnParams params = EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform[3] = pos;
		IEntity ent = GetGame().SpawnEntityPrefab(Resource.Load(m_pMapMarkerPrefab), null, params);
		SCR_MapDescriptorComponent mapdesc = SCR_MapDescriptorComponent.Cast(ent.FindComponent(SCR_MapDescriptorComponent));
		mapdesc.Item().SetBaseType(type);
		mapdesc.Item().SetDisplayName(name);
	}
	
	OVT_Faction GetOccupyingFaction()
	{
		return OVT_Faction.Cast(GetGame().GetFactionManager().GetFactionByKey(m_sOccupyingFaction));
	}
	
	void OVT_OverthrowConfigComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_Difficulty = new OVT_DifficultySettings();
	}
}