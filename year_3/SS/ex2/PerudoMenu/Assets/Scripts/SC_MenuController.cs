using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SC_MenuController : MonoBehaviour
{
    public SC_MenuLogic CurrMenuLogic;
    public SC_BackgamoonConnect backgamoon_connect;
    bool multiplayer = true;
    #region buttons
    public void Btn_Singleplayer()
    {
        multiplayer = false;
        Debug.Log("Btn_Singleplayer");
        multiplayer = false;
        if (CurrMenuLogic != null)
            CurrMenuLogic.Btn_Logic("Screen_Singleplayer");
    }
    public void btn_Play()
    {
        Debug.Log("btn_Play");
        if (CurrMenuLogic != null)
        {
            backgamoon_connect.set(multiplayer);
            //CurrMenuLogic.Btn_Logic("Screen_Loading");
            SceneManager.LoadScene("Backgamoon");
        }
    }

    public void Btn_Multiplayer()
    {
        Debug.Log("Btn_Multiplayer");
        multiplayer = true;
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

    public void Btn_Exit()
    {
        Debug.Log("Btn_Exit");
        if (CurrMenuLogic != null)
            CurrMenuLogic.Exit_Logic();
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


