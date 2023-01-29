#include "State.h"

void AboutInfoState::init()
{ }

void AboutInfoState::process(sf::Event& e)
{ }

void AboutInfoState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("About Info", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::PushFont(Sim.GetResources().LargeFont);
	CenteredText("About Cyanotypes");
	ImGui::PopFont();

	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, sf::Color::White);
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, sf::Color(225, 225, 225));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, sf::Color(225, 225, 225));

	ImGui::SetNextWindowBgAlpha(0);
	ImGui::SetNextWindowPos({ 10, 40 });
	ImGui::SetNextWindowSize({ 620, 380 });
	ImGui::Begin("Text", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	const char* text = 
		"Invented by Sir John Herschel in 1842, this simple printing process produces a monotone image of Prussian Blue"
		"using a photosensitive mixture of Ferric Ammonium Citrate and Potassium Ferricyanide. The negative film is placed"
		"on top of a paper coated with the mix, which covers parts of the paper, leaving the rest open."
		"\n\n"
		"When exposed to natural or artificial ultraviolet light, these salts are reduced to their ferrous state,"
		"producing a high contrast blue image when oxidised. Oxidation can be hastened by immersion in running water and"
		"hydrogen peroxide, which also washes away the unused iron salts."
		"\n\n"
		"Since this process uses iron compounds, it was cheaper than older methods using silver compounds, and thus "
		"the process was suited to cheaply reproduce technical drawings, its most common use being to create 'blueprints'."
		"\n\n"
		"This process was popularized by Anna Atkins, the first female photographer, who created a series of"
		"cyanotype books documenting ferns and other plant life from her extensive seaweed collection, placing"
		"specimens directly onto coated paper and allowing the action of light to create a silhouette effect."
		"\n\n"
		"While this process has been eclipsed by modern photocopiers, in recent decades, the cyanotype process has been"
		"rejuvenated by the artistic community, thanks to its rich blue tones and the ability to apply it to not only paper,"
		"but textiles and any other surfaces with can adsorb the mixture, to create beautiful blue designs and stunning artwork.";

	ImGui::PushStyleColor(ImGuiCol_Text, sf::Color::Black);
	ImGui::TextWrapped(text);
	ImGui::PopStyleColor();

	ImGui::End();
	ImGui::PopStyleColor(3);

	ImGui::SetCursorPos({ 10, HEIGHT - 50 });
	if (ImGui::Button("Back", { 80, 40 }))
	{
		Sim.PopState();
	}

	ImGui::End();
}