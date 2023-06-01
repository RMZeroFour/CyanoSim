#include "states/State.h"
#include <tinyfiledialogs.h>
#include <escapi.h>

void SelectPictureState::init()
{
	if (!Sim.GetResources().SelectedImage)
		Sim.GetResources().SelectedImage = std::make_shared<sf::Image>();

	std::shared_ptr<sf::Image> flowers = Sim.GetResources().Flowers;
	std::shared_ptr<sf::Image> selected = Sim.GetResources().SelectedImage;

	selected->create(flowers->getSize().x, flowers->getSize().y);
	selected->copy(*flowers, 0, 0);

	tex.create(selected->getSize().x, selected->getSize().y);
	tex.update(*selected);
}

void SelectPictureState::process(sf::Event& e)
{ }

void SelectPictureState::draw(sf::RenderWindow& window)
{
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize({WIDTH, HEIGHT});
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("Select Picture", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, sf::Color::White);
	ImGui::SetNextWindowPos(ImGui::GetStyle().ItemSpacing);
	ImGui::SetNextWindowSize({ImGui::GetContentRegionAvail().x, 40});
	ImGui::Begin("Text", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	std::string text = "Select a picture to create a cyanotype.";
	if (Sim.IsSimulating())
		text = "Step 1) " + text;
	ImGui::PushStyleColor(ImGuiCol_Text, sf::Color(65, 76, 96));
	ImGui::TextWrapped(text.c_str());
	ImGui::PopStyleColor();
	ImGui::End();
	ImGui::PopStyleColor();

	ImGui::Dummy({0, 50});

	ImGui::Columns(3);
	if (ImGui::Button("Use default image", {-1, 40}))
	{
		std::shared_ptr<sf::Image> flowers = Sim.GetResources().Flowers;
		std::shared_ptr<sf::Image> selected = Sim.GetResources().SelectedImage;

		selected->create(flowers->getSize().x, flowers->getSize().y);
		selected->copy(*flowers, 0, 0);

		tex.create(selected->getSize().x, selected->getSize().y);
		tex.update(*selected);
	}
	ImGui::NextColumn();
	if (ImGui::Button("Load from file", {-1, 40}))
	{
		const char* filter[] = {"*.PNG", "*.JPG"};
		char* filepath = tinyfd_openFileDialog("Select image", "", 2, filter, ".PNG/.JPG files", 0);

		if (filepath)
		{
			std::shared_ptr<sf::Image> selected = Sim.GetResources().SelectedImage;
			selected->loadFromFile(filepath);

			tex.create(selected->getSize().x, selected->getSize().y);
			tex.update(*selected);
		}
	}
	ImGui::NextColumn();
	if (ImGui::Button("Take from webcam", {-1, 40}))
	{
		const int CAPTURE_WIDTH = 640;
		const int CAPTURE_HEIGHT = 480;

		int devices = countCaptureDevices();

		if (devices != 0)
		{
			SimpleCapParams capture = {0};
			capture.mWidth = CAPTURE_WIDTH;
			capture.mHeight = CAPTURE_HEIGHT;
			capture.mTargetBuf = new int[CAPTURE_WIDTH * CAPTURE_HEIGHT];

			if (initCapture(0, &capture) != 0)
			{
				doCapture(0);

				while (!isCaptureDone(0))
					;

				sf::Image temp;
				temp.create(CAPTURE_WIDTH, CAPTURE_HEIGHT);

				for (size_t i = 0; i < CAPTURE_WIDTH; i++)
				{
					for (size_t j = 0; j < CAPTURE_HEIGHT; j++)
					{
						union
						{
							int packed;
							unsigned char channels[4];
						} conv;

						conv.packed = capture.mTargetBuf[j * capture.mWidth + i];
						temp.setPixel(i, j, sf::Color(conv.channels[2], conv.channels[1], conv.channels[0]));
					}
				}

				std::shared_ptr<sf::Image> selected = Sim.GetResources().SelectedImage;
				selected->create(temp.getSize().x, temp.getSize().y);
				selected->copy(temp, 0, 0);

				tex.create(CAPTURE_WIDTH, CAPTURE_HEIGHT);
				tex.update(temp);

				deinitCapture(0);
			}

			delete capture.mTargetBuf;
		}
	}
	ImGui::Columns(1);

	ImGui::Dummy({0, 10});
	CenteredImage(tex, {WIDTH - 200, HEIGHT - 200});

	ImGui::SetCursorPos({WIDTH - 90, HEIGHT - 50});
	if (ImGui::Button("Next", {80, 40}))
	{
		if (Sim.IsSimulating())
		{
			auto mss = std::make_unique<MixSolutionsState>(Sim);
			Sim.PushState(std::move(mss));
		}
		else
		{
			auto rte = std::make_unique<RunToEndState>(Sim);
			Sim.PushState(std::move(rte));
		}
	}

	ImGui::End();
}