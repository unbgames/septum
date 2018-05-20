#pragma once
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "Component.h"
#include <memory>

using std::shared_ptr;

class Text: public Component {
	public:
		enum TextStyle {
			SOLID, SHADED, BLENDED
		};
		Text (GameObject& associated, string fontFile, int fontSize,
				TextStyle style, string text, SDL_Color color);
		~Text ();

		/**
		 * Updates component state
		 * @param dt
		 */
		void Update (float dt);
		/**
		 * Renders the component
		 */
		void Render ();
		/**
		 * Checks if the Component is from the passed type
		 * @param type type to be checked
		 * @retval true the passed type is Text
		 * @retval false the passed type is not Text
		 */
		bool Is (string type) const;

		void SetText (string text);
		void SetColor (SDL_Color color);
		void SetStyle (TextStyle style);
		void SetFontFile (string fontFile);
		void SetFontSize (int fontSize);

	private:
		void RemakeTexture ();
		shared_ptr<TTF_Font> font;
		SDL_Texture* texture;

		string text;
		TextStyle style;
		string fontFile;
		int fontSize;
		SDL_Color color;
		int width = 0;
		int height = 0;
};
