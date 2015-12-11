using UnityEngine;
using System.Collections;

public class lostScene : MonoBehaviour {

	// Use this for initialization
	void Start () {
        Invoke("restartGame", 4);
    }
	
	// Update is called once per frame
	void Update () {
	
	}

    void restartGame() {
        Application.LoadLevel("mainScene");
    }
}
