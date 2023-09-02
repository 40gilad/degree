using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class SC_MenuController : MonoBehaviour
{
    public SC_MenuLogic CurrMenuLogic;

    #region buttons
    public void Btn_Singleplayer()
    {
        Debug.Log("Btn_Singleplayer");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Btn_Logic("Screen_Singleplayer");
    }
    public void btn_Play()
    {
        Debug.Log("btn_Play");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Btn_Logic("Screen_Loading");
    }

    public void Btn_Multiplayer()
    {
        Debug.Log("Btn_Multiplayer");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Btn_Logic("Screen_Multiplayer");
    }
    public void Btn_StudnetInfo()
    {
        Debug.Log("Btn_StudnetInfo");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Btn_Logic("Screen_StudnetInfo");
    }
    public void Btn_Options()
    {
        Debug.Log("Btn_Options");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Btn_Logic("Screen_Options");
    }
    public void Btn_Back()
    {
        Debug.Log("Btn_Back");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Btn_BackLogic();
    }

    public void btn_Linkedin()
    {
        Debug.Log("btn_Linkedin");
        Application.OpenURL("www.linkedin.com/in/gilad-meir");

    }

    public void Slider_Volume()
    {
        Debug.Log("Volume");
        if (CurrMenuLogic != null)
            CurrMenuLogic.VolumeLogic();
    }

    public void Music_Volume()
    {
        Debug.Log("Music_Volume");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Music_VolumeLogic();
    }


    public void Sfx_Volume()
    {
        Debug.Log("Sfx_Volume");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Sfx_VolumeLogic();
    }
    #endregion
}


