
function toggle_folder(title,content)
{
	if(document.getElementById)
	{
		var   vt = document.getElementById(title);
		var   vc = document.getElementById(content);

		if(vc.style.display != "block")
		{
			vt.style.background = "url(../o.png) no-repeat";
			vc.style.display = "block";
		}
		else
		{
			vt.style.background = "url(../c.png) no-repeat";
			vc.style.display = "none";
		}
	}
}
