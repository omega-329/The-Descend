#include "../Header/CodexState.h"
#include "../Header/Game.h"
#include "../Header/Entity.h"
#include "../Header/Limb.h"

#include <algorithm>
#include <sstream>

namespace
{
    constexpr float kWidth         = 1200.f;
    constexpr float kColumnWidth   = kWidth / 3.f;   // 400
    constexpr float kContentTop    = 96.f;
    constexpr float kContentBottom = 742.f;

    constexpr float kListRowHeight = 30.f;

    constexpr float kPortraitX = 440.f;
    constexpr float kPortraitY = 219.f;
    constexpr float kPortraitW = 320.f;
    constexpr float kPortraitH = 400.f;

    constexpr float kTextX        = kColumnWidth * 2.f + 20.f;   // 820
    constexpr float kDescTop      = 148.f;
    constexpr float kDividerY     = 420.f;

    constexpr float kStatsTop        = 490.f;
    constexpr float kStatsRowHeight  = 26.f;
    constexpr int   kStatsRows       = 9;

    constexpr const char* kLockedName        = "???";
    constexpr const char* kLockedDescription = "No record. This one has not crossed your path yet.";
    constexpr const char* kLockedStats       = "No data.";

    // Naive word wrap: SFML has no built-in wrapping, so we measure as we go.
    std::string wrapText(const sf::Font& font,
                         const std::string& text,
                         unsigned size,
                         float maxWidth,
                         int maxLines)
    {
        sf::Text measure(font, "", size);
        std::istringstream words(text);

        std::string word;
        std::string line;
        std::string result;
        int lines = 0;

        while (words >> word)
        {
            std::string candidate = line.empty() ? word : line + " " + word;
            measure.setString(candidate);

            if (!line.empty() && measure.getLocalBounds().size.x > maxWidth)
            {
                if (lines + 1 >= maxLines)
                {
                    result += line + " ...";
                    return result;
                }

                result += line + "\n";
                line = word;
                ++lines;
            }
            else
            {
                line = candidate;
            }
        }

        if (!line.empty())
            result += line;

        return result;
    }
}

CodexState::CodexState(Game& game)
    : game(game)
    , monsters(game.getCodex().monsters())
    , characters(game.getCodex().characters())
    , title(game.getFont(), "THE CODEX", 44)
    , hint(game.getFont(), "UP/DOWN  browse      LEFT/RIGHT  turn page      ESC  back", 18)
{
    for (const auto& monster : monsters)
        entries.push_back({&monster});

    for (const auto& character : characters)
        entries.push_back({&character});

    title.setOrigin(title.getLocalBounds().getCenter());
    title.setPosition({kWidth / 2.f, 42.f});
    title.setFillColor(sf::Color(190, 40, 40));

    hint.setOrigin(hint.getLocalBounds().getCenter());
    hint.setPosition({kWidth / 2.f, 772.f});
    hint.setFillColor(sf::Color(110, 110, 110));

    for (const Entry& entry : entries)
    {
        wrappedDescriptions.push_back(
            wrapText(game.getFont(), entry.entity->getDescription(), 20, kColumnWidth - 40.f, 10));
    }
}

bool CodexState::isLocked(int index) const
{
    if (index < 0 || index >= static_cast<int>(entries.size()))
        return false;

    const Entry& entry = entries[index];
    return !game.getCodex().isSeen(entry.entity->getName());
}

void CodexState::moveSelection(int delta)
{
    if (entries.empty())
        return;

    const int count = static_cast<int>(entries.size());
    selected = (selected + delta + count) % count;
    statsPage = 0;                   // a different entity has a different limb count
}

int CodexState::pageCount() const
{
    if (entries.empty())
        return 1;

    const int limbs = entries[selected].entity->getLimbCount();
    return std::max(1, (limbs + kStatsRows - 1) / kStatsRows);
}

int CodexState::lastPage() const
{
    return pageCount() - 1;
}

void CodexState::handleEvent(const sf::Event& event)
{
    auto* key = event.getIf<sf::Event::KeyPressed>();
    if (!key)
        return;

    switch (key->code)
    {
        case sf::Keyboard::Key::Up:
            moveSelection(-1);
            break;

        case sf::Keyboard::Key::Down:
            moveSelection(1);
            break;

        case sf::Keyboard::Key::Left:
            if (!isLocked(selected) && statsPage > 0)
                --statsPage;
            break;

        case sf::Keyboard::Key::Right:
            if (!isLocked(selected) && statsPage < lastPage())
                ++statsPage;
            break;

        case sf::Keyboard::Key::Escape:
            game.popState();
            return;                  // 'this' is destroyed by popState

        default:
            break;
    }
}

void CodexState::update(float)
{
}

void CodexState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(9, 9, 11));

    sf::Font& font = game.getFont();

    // --- three backgrounds, so the columns are visible even with no text ---
    const float contentHeight = kContentBottom - kContentTop;
    sf::RectangleShape column({kColumnWidth, contentHeight});

    column.setPosition({0.f, kContentTop});
    column.setFillColor(sf::Color(16, 16, 19));
    window.draw(column);

    column.setPosition({kColumnWidth, kContentTop});
    column.setFillColor(sf::Color(11, 11, 14));
    window.draw(column);

    column.setPosition({kColumnWidth * 2.f, kContentTop});
    column.setFillColor(sf::Color(16, 16, 19));
    window.draw(column);

    // --- vertical dividers ---
    sf::RectangleShape divider({1.f, contentHeight});
    divider.setFillColor(sf::Color(70, 60, 60));

    divider.setPosition({kColumnWidth, kContentTop});
    window.draw(divider);

    divider.setPosition({kColumnWidth * 2.f, kContentTop});
    window.draw(divider);

    // --- divider that splits column 3 into description / stats ---
    sf::RectangleShape hDivider({kColumnWidth, 1.f});
    hDivider.setFillColor(sf::Color(70, 60, 60));
    hDivider.setPosition({kColumnWidth * 2.f, kDividerY});
    window.draw(hDivider);

    window.draw(title);
    drawList(window, font);
    drawPortrait(window, font);
    drawDescription(window, font);
    drawStats(window, font);
    window.draw(hint);
}

void CodexState::drawList(sf::RenderWindow& window, sf::Font& font) const
{
    const float x = 24.f;
    float y = kContentTop + 16.f;

    auto header = [&](const std::string& text)
    {
        sf::Text label(font, text, 22);
        label.setFillColor(sf::Color(150, 40, 40));
        label.setPosition({x, y});
        window.draw(label);
        y += 34.f;
    };

    header("MONSTERS");

    for (int i = 0; i < static_cast<int>(entries.size()); ++i)
    {
        if (i == static_cast<int>(monsters.size()))
        {
            y += 16.f;
            header("CHARACTERS");
        }

        const bool locked = isLocked(i);

        std::string text = locked ? std::string(kLockedName) : entries[i].entity->getName();
        if (i == selected)
            text = "> " + text;

        sf::Text row(font, text, 22);

        if (i == selected)
            row.setFillColor(sf::Color::White);
        else if (locked)
            row.setFillColor(sf::Color(85, 84, 80));
        else
            row.setFillColor(sf::Color(140, 138, 130));

        row.setPosition({x, y});
        window.draw(row);

        y += kListRowHeight;
    }
}

void CodexState::drawPortrait(sf::RenderWindow& window, sf::Font& font) const
{
    // Frame first, so the selected entry always looks "placed" even if its
    // texture is missing.
    sf::RectangleShape frame({kPortraitW, kPortraitH});
    frame.setPosition({kPortraitX, kPortraitY});
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color(60, 55, 55));
    frame.setOutlineThickness(1.f);
    window.draw(frame);

    if (entries.empty())
        return;

    const float centerX = kPortraitX + kPortraitW / 2.f;
    const float centerY = kPortraitY + kPortraitH / 2.f;

    if (isLocked(selected))
    {
        sf::Text mark(font, "?", 160);
        mark.setOrigin(mark.getLocalBounds().getCenter());
        mark.setPosition({centerX, centerY});
        mark.setFillColor(sf::Color(45, 45, 50));
        window.draw(mark);
        return;
    }

    const sf::Texture& texture = game.getCodex().textureFor(entries[selected].entity->getName());
    const sf::Vector2u size = texture.getSize();

    if (size.x == 0 || size.y == 0)
        return;

    // Keep the aspect ratio and fit the whole sprite inside the frame.
    const float scale = std::min(kPortraitW / static_cast<float>(size.x),
                                 kPortraitH / static_cast<float>(size.y));

    sf::Sprite sprite(texture);
    sprite.setOrigin({size.x / 2.f, size.y / 2.f});
    sprite.setScale({scale, scale});
    sprite.setPosition({centerX, centerY});
    window.draw(sprite);
}

void CodexState::drawDescription(sf::RenderWindow& window, sf::Font& font) const
{
    if (entries.empty())
        return;

    const bool locked = isLocked(selected);

    sf::Text heading(font, "DESCRIPTION", 20);
    heading.setFillColor(sf::Color(150, 40, 40));
    heading.setPosition({kTextX, kContentTop + 16.f});
    window.draw(heading);

    std::string text = locked ? std::string(kLockedDescription) : wrappedDescriptions[selected];

    sf::Text description(font, text, 20);
    description.setFillColor(locked ? sf::Color(120, 118, 110) : sf::Color(200, 198, 190));
    description.setPosition({kTextX, kDescTop});
    window.draw(description);
}

void CodexState::drawStats(sf::RenderWindow& window, sf::Font& font) const
{
    if (entries.empty())
        return;

    sf::Text heading(font, "STATS", 20);
    heading.setFillColor(sf::Color(150, 40, 40));
    heading.setPosition({kTextX, kDividerY + 14.f});
    window.draw(heading);

    if (isLocked(selected))
    {
        sf::Text none(font, kLockedStats, 19);
        none.setFillColor(sf::Color(120, 118, 110));
        none.setPosition({kTextX, kDividerY + 48.f});
        window.draw(none);
        return;
    }

    const Entity& entity = *entries[selected].entity;

    sf::Text nameHeader(font, "LIMB", 16);
    nameHeader.setFillColor(sf::Color(120, 118, 110));
    nameHeader.setPosition({kTextX, kDividerY + 44.f});
    window.draw(nameHeader);

    sf::Text hpHeader(font, "HP", 16);
    hpHeader.setFillColor(sf::Color(120, 118, 110));
    hpHeader.setPosition({kTextX + 230.f, kDividerY + 44.f});
    window.draw(hpHeader);

    sf::Text dmgHeader(font, "DMG", 16);
    dmgHeader.setFillColor(sf::Color(120, 118, 110));
    dmgHeader.setPosition({kTextX + 310.f, kDividerY + 44.f});
    window.draw(dmgHeader);

    const int limbs = entity.getLimbCount();
    const int first = statsPage * kStatsRows;
    const int last = std::min(limbs, first + kStatsRows);

    float y = kStatsTop;

    for (int i = first; i < last; ++i)
    {
        const Limb& limb = entity.getLimb(i);

        sf::Text name(font, limb.getName(), 19);
        name.setFillColor(sf::Color(200, 198, 190));
        name.setPosition({kTextX, y});
        window.draw(name);

        sf::Text hp(font, std::to_string(static_cast<int>(limb.getMaxHP())), 19);
        hp.setFillColor(sf::Color(200, 198, 190));
        hp.setPosition({kTextX + 230.f, y});
        window.draw(hp);

        sf::Text dmg(font, std::to_string(static_cast<int>(limb.getDMG())), 19);
        dmg.setFillColor(sf::Color(160, 90, 90));
        dmg.setPosition({kTextX + 310.f, y});
        window.draw(dmg);

        y += kStatsRowHeight;
    }

    if (pageCount() > 1)
    {
        sf::Text page(font,
                      "PAGE " + std::to_string(statsPage + 1) + " / " + std::to_string(pageCount()),
                      16);
        page.setFillColor(sf::Color(120, 118, 110));
        page.setPosition({kTextX, kStatsTop + kStatsRows * kStatsRowHeight + 4.f});
        window.draw(page);
    }
}
